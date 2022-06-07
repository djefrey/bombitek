/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** Server
*/

#pragma once

#include "network/IServer.hpp"
#include "../sockets/ISocket.hpp"
#include "../sockets/SocketInclude.hpp"
#include <memory>
#include <map>

#ifdef _WIN32

namespace network {
    class WinServer : public IServer {
        std::unique_ptr<ISocket> _socket;
        std::map<ConnId,uint64_t> _clients;

        std::string _ip;
        unsigned short _port;

        fd_set _readSet;
        fd_set _writeSet;

        public:
        WinServer(const std::string &ip = "", const std::string &port = "", const int maxClient = 4);
        ~WinServer() = default;

        void updateRWStates();

        bool canAcceptConn();
        bool canRead(ConnId id);
        bool canWrite(ConnId id);

        ConnId acceptClient();
        int read(ConnId id, void *buf, std::size_t size);
        void write(ConnId id, void *data, std::size_t size);

        unsigned short getServerPort() const { return _port; };
        const std::string &getServerIp() const { return _ip; };

        void setPortFromSocket();
        std::string findIp();
    };
}

#endif
