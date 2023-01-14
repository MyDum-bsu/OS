#include "socket/client/client.h"
#include "socket/server/server.h"

void write_to_server(Client client, const char *message);

void child() {
    Client client("socket.server");
    client.Write("hi");
    sleep(1);
    puts(client.Read());
//    Server s("s.server");
//    puts(s.Receive());
//    s.Close();
    sleep(5);
}

void parent() {
    Server server("socket.server");
    puts(server.Receive());
    server.Send("Hello!!!!");
    sleep(3);
    server.Close();
}

int main() {
    Server server("s.server");
    Client client("s.server");
    pid_t pid = fork();
    if (0 == pid) {
        client.Write("Hello, I'm client");
    } else {
        puts(server.Receive());
        server.Send("Hello, I'm server");
    }
    if (0 == pid) {
        puts(client.Read());
        _exit(0);
    }
    server.Close();
    return 0;
}

