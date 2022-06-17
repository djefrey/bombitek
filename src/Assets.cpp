/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Assets
*/

#include "Assets.hpp"
#include "raylib/TextureManager.hpp"
#include "raylib/ModelManager.hpp"
#include "raylib/AnimationManager.hpp"
#include "raylib/FontManager.hpp"
#include "raylib/ShaderManager.hpp"
#include "raylib/SoundManager.hpp"

void bomberman::loadTextures(ecs::World &world)
{
    raylib::TextureManager &textureMan = world.getRessource<raylib::TextureManager>();

    textureMan.loadTexture("logo", "./assets/textures/logo.png");
    textureMan.loadTexture("epitech", "./assets/textures/epitech.png");
    textureMan.loadTexture("button", "./assets/textures/button.png");
    textureMan.loadTexture("large_button", "./assets/textures/large_button.png");
    textureMan.loadTexture("square_button", "./assets/textures/square_button.png");

    textureMan.loadTexture("bottle", "./assets/textures/bottle.png");
    textureMan.loadTexture("table", "./assets/textures/table.png");
    textureMan.loadTexture("chair", "./assets/textures/chair.png");
    textureMan.loadTexture("bag", "./assets/textures/bag.png");
    textureMan.loadTexture("ground", "./assets/textures/ground.png");
    textureMan.loadTexture("water", "./assets/textures/water.png");

    textureMan.loadTexture("timothe", "./assets/textures/timothe.png");
    textureMan.loadTexture("ludovic", "./assets/textures/ludo.png");
    textureMan.loadTexture("mathieu", "./assets/textures/mathieu.png");
    textureMan.loadTexture("jeffrey", "./assets/textures/jeffrey.png");
}

void bomberman::loadModels(ecs::World &world)
{
    raylib::ModelManager &modelMan = world.getRessource<raylib::ModelManager>();

    modelMan.loadModel("button", "./assets/models/button.iqm");
    modelMan.loadModel("large_button", "./assets/models/large_button.iqm");
    modelMan.loadModel("square_button", "./assets/models/square_button.iqm");
    modelMan.loadModel("logo", "./assets/models/logo.iqm");

    modelMan.loadModel("bottle", "./assets/models/bottle.iqm");
    modelMan.loadModel("table", "./assets/models/table.iqm");
    modelMan.loadModel("chair", "./assets/models/chair.iqm");
    modelMan.loadModel("bag", "./assets/models/bag.iqm");
    modelMan.loadModel("water", "./asstes/models/water.iqm");

    modelMan.loadModel("player", "./assets/models/player.iqm");
}

void bomberman::loadAnimations(ecs::World &world)
{
    raylib::AnimationManager &animMan = world.getRessource<raylib::AnimationManager>();

    animMan.loadAnimations("playerAnims", "./assets/models/player.iqm");
}

void bomberman::loadFonts(ecs::World &world)
{
    raylib::FontManager &fontMan = world.getRessource<raylib::FontManager>();

    fontMan.loadFont("emulogic", "./assets/fonts/emulogic.ttf");
}

void bomberman::loadShaders(ecs::World &world)
{
    raylib::ShaderManager &shaderMan = world.getRessource<raylib::ShaderManager>();

    // shaderMan.loadShader("button", "./assets/shaders/button.vs", "./assets/shaders/button.fs");
}

void bomberman::loadSounds(ecs::World &world)
{
    raylib::SoundManager &soundMan = world.getRessource<raylib::SoundManager>();

    soundMan.loadSound("main_menu_music", "./assets/sounds/main_menu.mp3", true);
}

void bomberman::applyAssetsToModels(ecs::World &world)
{
    raylib::TextureManager &textureMan = world.getRessource<raylib::TextureManager>();
    raylib::ModelManager &modelMan = world.getRessource<raylib::ModelManager>();

    modelMan.getModel("logo").getMaterialView(0)
    .setTexture(textureMan.getTexture("logo"));

    modelMan.getModel("large_button").getMaterialView(0)
    .setTexture(textureMan.getTexture("large_button"));

    modelMan.getModel("square_button").getMaterialView(0)
    .setTexture(textureMan.getTexture("square_button"));

    modelMan.getModel("button").getMaterialView(0)
    .setTexture(textureMan.getTexture("button"));

    modelMan.getModel("bottle").getMaterialView(0)
    .setTexture(textureMan.getTexture("bottle"));

    modelMan.getModel("table").getMaterialView(0)
    .setTexture(textureMan.getTexture("table"));

    modelMan.getModel("chair").getMaterialView(0)
    .setTexture(textureMan.getTexture("chair"));

    modelMan.getModel("bag").getMaterialView(0)
    .setTexture(textureMan.getTexture("bag"));

    modelMan.getModel("water").getMaterialView(0)
    .setTexture(textureMan.getTexture("water"));

    modelMan.getModel("player").getMaterialView(0)
    .setTexture(textureMan.getTexture("timothe"));
}