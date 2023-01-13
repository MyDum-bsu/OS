#include "socket/client/client.h"
#include "socket/server/server.h"

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
    int pid = fork();
    if (pid == 0) {
        client.Write("Hello, I'm client");
    }
        puts(server.Receive());
        server.Send("Hello, I'm server");
        puts(client.Read());
        server.Close();
}
