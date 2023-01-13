#include "pipe.h"

Pipe::Pipe(const char *name) {
    this->name = (char *) malloc(64);
    buffer = (char *) malloc(512);
    mkfifo(name, 0666);
    strcpy(this->name, name);
}

char *Pipe::Read() {
    fileDescriptor = open(name, O_RDONLY);
    read(fileDescriptor, buffer, 512);
    close(fileDescriptor);
    return buffer;
}

void Pipe::Write(const char *message) {
    fileDescriptor = open(name, O_WRONLY);
    write(fileDescriptor, message, strlen(message));
    close(fileDescriptor);
}