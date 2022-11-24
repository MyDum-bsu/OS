#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <sys/wait.h>
#include <algorithm>

char **getArgs(const std::vector<std::string> &toKillByName, const std::vector<int> &toKillById) {
    int argc = toKillByName.size() + toKillById.size() + 2;
    char **argv = new char *[argc + 1];

    argv[0] = new char[sizeof("--name")];
    strcpy(argv[0], "--name");
    int i = 1;
    for (auto &name: toKillByName) {
        argv[i] = new char[name.length() + 1];
        strcpy(argv[i], name.c_str());
        ++i;
    }
    argv[i] = new char[sizeof("--id")];
    strcpy(argv[i], "--id");
    i++;
    for (auto id: toKillById) {
        std::string str = std::to_string(id);
        argv[i] = new char[str.length() + 1];
        strcpy(argv[i], str.c_str());
        ++i;
    }
    return argv;
}

const std::string KILLER_PATH = "../../killer/cmake-build-debug/killer";

std::string join(const std::vector<std::string> &vector, const std::string &delimiter) {
    std::string result;
    for (auto i = 0; i < vector.size(); ++i) {
        result += vector[i];
        if (i != vector.size() - 1) {
            result += delimiter;
        }
    }
    return result;
}

void killAll(const std::vector<std::string> &toKillByName,
             const std::vector<int> &toKillById,
             const std::vector<std::string> &toKillByEnvVar) {
    std::string env_var = join(toKillByEnvVar, ",");
    char buff[8841];
    strcpy(buff, env_var.c_str());
    setenv("PROC_TO_KILL", buff, 1);
    int pid = fork();

    if (pid == 0) {
        int argc = toKillByName.size() + toKillById.size() + 2;
        char **argv = getArgs(toKillByName, toKillById);
        execv(KILLER_PATH.c_str(), argv);
        for (int i = 0; i < argc; ++i) {
            delete[] argv[i];
        }
        delete[] argv;
        exit(0);
    } else if (pid == -1) {
        unsetenv("PROC_TO_KILL");
        exit(pid);
    }
    int status;
    waitpid(pid, &status, 0);
    unsetenv("PROC_TO_KILL");
}

int main() {
    std::vector<std::string> toKillByName = {"telegram-deskto"};
    std::vector<int> toKillById = {6346};
    std::vector<std::string> toKillByEnvVar = {"yandex_browser"};
    system("top");
    std::cout << "Killing...\n";
    killAll(toKillByName, toKillById, toKillByEnvVar);
    sleep(1);
    system("top");
    return 0;
}