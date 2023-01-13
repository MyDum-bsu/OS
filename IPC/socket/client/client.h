#ifndef IPC_CLIENT_H
#define IPC_CLIENT_H

#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

class Client {
public:
    Client(const char *path);

    int Connect();

    char *Read();

    int Write(const char *message);

private:
    int sock;
    sockaddr_un address;
    char* text;
    int serverSocket;
};

#endif //IPC_CLIENT_H
