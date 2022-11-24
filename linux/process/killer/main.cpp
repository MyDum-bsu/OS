#include <string>
#include <cstring>
#include <iostream>
#include <sstream>

void killer(int argc, char **pString);

void killProcessByName(const char *string);

void killProcessById(int id);

int main(int argc, char *argv[]) {
    killer(argc,argv);
    char buff[100];
    if (getenv("PROC_TO_KILL") == nullptr)
        return 0;

    strcpy(buff, getenv("PROC_TO_KILL"));
    std::stringstream ss(buff);
    while (ss.getline(buff, sizeof(buff), ',')) {
        killProcessByName(buff);
    }
    return 0;
}

void killer(int argc, char **pString) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(pString[i], "--name") == 0) {
            killProcessByName(pString[i + 1]);
        } else if (strcmp(pString[i], "--id") == 0) {
            killProcessById(std::stoi(pString[i + 1]));
        }
    }
}

void killProcessById(int id) {
    system(("kill" + std::to_string(id)).c_str());
}

void killProcessByName(const char *string) {
    system(("killall " + std::string(string)).c_str());
}
