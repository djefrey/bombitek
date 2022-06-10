/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** main
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include "ecs/engine/EntityCommands.hpp"
#include "ecs/engine/Network.hpp"
#include "ecs/engine/InternalServer.hpp"

#include "raylib/Camera.hpp"
#include "raylib/Window.hpp"
#include "raylib/TextureManager.hpp"
#include "raylib/ModelManager.hpp"
#include "raylib/AnimationManager.hpp"
#include "raylib/FontManager.hpp"

#include "ecs/components/DrawableCube.hpp"
#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/Hitbox.hpp"
#include "ecs/components/Clickable.hpp"
#include "ecs/components/Hoverable.hpp"
#include "ecs/components/HoverTint.hpp"
#include "ecs/components/Text3D.hpp"
#include "ecs/components/ColorTexture.hpp"

#include "network/sockets/SocketError.hpp"

int WSA(void);

void registerBasicComponents(ecs::World &world)
{
    world.registerComponents<Transform, ecs::Tint, ecs::MirrorEntity, ecs::Hitbox>();
}

void registerRender(ecs::World &world)
{
    world.registerComponents<ecs::DrawableCube, ecs::TextureRef>();
    world.registerSystem<ecs::DrawTextureCubeSystem>();

    world.registerComponent<ecs::ModelRef>();
    world.registerSystem<ecs::DrawableModelSystem>();

    world.registerComponents<ecs::Text3D, ecs::FontRef>();
    world.registerSystem<ecs::Draw3DTextSystem>();
}

void registerMouseInputs(ecs::World &world)
{
    world.registerComponents<ecs::Clickable, ecs::Hoverable>();
    world.registerSystems<ecs::ClickUpdateSystem, ecs::HoverUpdateSystem, ecs::HoverTintUpdateSystem>();
}

class InputSystem : public ecs::ASystem {
    public:
    void setSignature(ecs::ComponentManager &man)
    {
        _signature = man.generateSignature<Transform, ecs::MirrorEntity>();
    }

    void update(ecs::World &world)
    {
        for (ecs::Entity entity : _entities) {
            Transform &transform = world.getComponent<Transform>(entity);
            Vector3 &pos = transform.translation;

            if (IsKeyDown(KEY_W))
                pos.z -= 0.05;
            else if (IsKeyDown(KEY_S))
                pos.z += 0.05;

            if (IsKeyDown(KEY_A))
                pos.x -= 0.05;
            else if (IsKeyDown(KEY_D))
                pos.x += 0.05;

            if (IsKeyDown(KEY_Q))
                pos.y += 0.05;
            else if (IsKeyDown(KEY_E))
                pos.y -= 0.05;

            if (world.hasComponent<ecs::Tint>(entity)) {
                if (IsKeyDown(KEY_R))
                    world.getComponent<ecs::Tint>(entity) = RED;
                if (IsKeyDown(KEY_G))
                    world.getComponent<ecs::Tint>(entity) = GREEN;
                if (IsKeyDown(KEY_B))
                    world.getComponent<ecs::Tint>(entity) = BLUE;
            }
        }
    }
};

#include "raylib/GL.hpp"

class DrawCubeTest : public ecs::ASystem {
    public:
    DrawCubeTest() { _stage = ecs::DRAW_WORLD; };

    void setSignature(ecs::ComponentManager &man)
    {
        _signature = man.generateSignature<Transform, ecs::Tint>();
    }

    void update(ecs::World &world)
    {
        raylib::Camera &cam = world.getRessource<raylib::Camera>();

        cam.begin3DMode();
        for (ecs::Entity entity : _entities) {
            Transform &transform = world.getComponent<Transform>(entity);
            ecs::Tint &tint = world.getComponent<ecs::Tint>(entity);
            raylib::Matrix mat = raylib::Matrix::fromTransform(transform);

            raylib::RlMatrixPush push;
            raylib::rlMultMatrix(mat);
            DrawCube({0}, 1, 1, 1, tint);
        }
        cam.end3DMode();
    }
};

void runClient(ecs::World &world)
{
// ---------------------------------

    // registerRender(world);
    // registerMouseInputs(world);

}

void serverMain(ecs::World *world, bool *run)
{
    std::cerr << " --- Start server !" << std::endl;
    registerBasicComponents(*world);

    world->insertRessource<ecs::ServerManager>();
    world->registerSystem<ecs::NetworkUpdateSystem<ecs::ServerManager>>();

    world->getRessource<ecs::ServerManager>().startServer();

    std::cerr << "-- Run server !" << std::endl;
    while (*run)
        world->updateServer();
}

int main(int ac, char **av)
{
    #ifdef _WIN32
    if (WSA() == 84)
        return (84);
    #endif
    ecs::World world{};

    registerBasicComponents(world);

    world.insertRessource<raylib::Window>();
    world.insertRessource<raylib::Camera>(Vector3 {0.0, 0.0, 2.0}, Vector3 {0.0, 0.0, -4.0});
    world.insertRessource<raylib::TextureManager>();
    world.insertRessource<raylib::ModelManager>();
    world.insertRessource<raylib::AnimationManager>();
    world.insertRessource<raylib::FontManager>();
    world.insertRessource<ecs::ClientManager>();

    world.registerSystem<ecs::NetworkUpdateSystem<ecs::ClientManager>>();
    world.registerSystems<InputSystem, DrawCubeTest>();

    world.insertRessource<ecs::InternalServer>();

// ---------------------------------

    raylib::Texture &woodPlanks = world.getRessource<raylib::TextureManager>().loadTexture("./assets/textures/planks.png");

    world.spawn().insert(Transform{{1, 1, -2}, QuaternionIdentity(), {1, 1, 1}}, GREEN, ecs::MirrorEntity{});

// ---------------------------------

    if (ac == 2)
        world.getRessource<ecs::InternalServer>().startServer(serverMain);

    int tries = 0;
    for (; tries < 5; tries++) {
        try {
        std::cout << "Try to connect to server" << std::endl;
            world.getRessource<ecs::ClientManager>().connectTo();
            break;
        } catch(network::SocketError) {
            std::cout << "Failed to connect to server (" << tries + 1 << "/5)" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    if (tries == 5)
        return 1;

    raylib::Window &window = world.getRessource<raylib::Window>();

    window.setTargetFPS(60);
    window.resize({640, 480});
    while (!window.shouldClose())
        world.updateClient();
}
