#include <iostream>
#include <cstring>
#include <sys/wait.h>
#include "unistd.h"

void read_from_channel(int channel[2]) {
    char buffer[4096] = {};
    ssize_t count;
    while (true) {
        count = read(channel[0], buffer, sizeof buffer);
        if (count <= 0) {
            puts("No more data in channel");
            break;
        }
        printf("Got %zd bytes from pipe : %s\n", count, buffer);
    }
}

void write_to_channel(int channel[2], const char *data) {
    write(channel[1], data, strlen(data));
    close(channel[1]);
}

int main() {
    int first_channel[2];
    pipe(first_channel);
    pid_t pid = fork();
    if (0 == pid) {
        close(first_channel[0]);
        write_to_channel(first_channel, "Hello");
    }
    close(first_channel[1]);
    read_from_channel(first_channel);

    int second_channel[2];
    pipe(second_channel);
    write_to_channel(second_channel, "Dad");
    if (0 == pid) {
        close(second_channel[1]);
        read_from_channel(second_channel);
        _exit(0);
    }

    wait(nullptr);

    return 0;
}