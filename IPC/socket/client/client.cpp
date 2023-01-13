#include <cstdio>
#include <string>
#include "client.h"

Client::Client(const char *path) {
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, path);
    Connect();
}

int Client::Connect() {
    return serverSocket = connect(sock, (struct sockaddr *) &address, sizeof(address));
}

int Client::Write(const char *message) {
    return send(sock, message, strlen(message), 0);
}
char* Client::Read() {
    read(serverSocket, text, 1024);
    puts(std::to_string(errno).c_str());
    return text;
}