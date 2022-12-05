#include <iostream>
#include <unistd.h>

const std::string path[]{
        "../../M/cmake-build-debug/M",
        "../../A/cmake-build-debug/A",
        "../../P/cmake-build-debug/P",
        "../../S/cmake-build-debug/S"
};

int main() {
    int p[3], pid;
    std::string line;
    for (int i = 0; i < 3; i++) {
        pipe(p);
        pid = fork();
        if (!pid) {
            dup2(p[1], 1);
            system(path[i].c_str());
            exit(0);
        }
        dup2(p[0],0);
        close(p[1]);
    }
    system(path[3].c_str());
    return 0;
}
