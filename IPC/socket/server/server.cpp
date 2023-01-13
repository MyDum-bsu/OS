#include <csignal>
#include <iostream>
#include "server.h"

Server::Server(const char *path) {
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    address.sun_family = AF_UNIX;

    strcpy(address.sun_path, path);
    unlink(path);
    int optionValue = 1;
//    if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT,
//                   &optionValue, sizeof(optionValue)) == -1)
//    {
//        throw std::runtime_error("setsockopt");
//    }
    if (bind(sock, (sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << errno;
        throw std::runtime_error("bind");
    }
    if (listen(sock, SOMAXCONN) == -1) {
        throw std::runtime_error("listen");
    }
    puts("server is listening......");
    newSocket = accept(sock, NULL, NULL); // не sock, а некий внешний (передаваемый) socket ?
    if (newSocket == -1) {
        throw std::runtime_error("accept");
    }
}

const char *Server::Receive() const {
    read(newSocket, buffer, 512);
    return buffer;
}

void Server::Close() const {
    close(newSocket);
}

void Server::Send(const char *message) const {
    send(newSocket, message, strlen(message), 0);
}
