#ifndef IPC_PIPE_H
#define IPC_PIPE_H

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>

class Pipe {
public:
    explicit Pipe(const char *name);

    char *Read();

    void Write(const char *message);

private:
    char *name;
    int fileDescriptor;
    char *buffer;
};

#endif //IPC_PIPE_H
