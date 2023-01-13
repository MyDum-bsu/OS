#ifndef IPC_SERVER_H
#define IPC_SERVER_H

#include <stdexcept>
#include <sys/socket.h>
#include <sys/un.h>

class Server {
public:
    explicit Server(const char *path);
    const char* Receive() const;
    void Send(const char* message) const;
    void Close() const;
private:
    int sock;
    int newSocket;
    char* buffer = new char[512];
    sockaddr_un address;
};

#endif //IPC_SERVER_H
