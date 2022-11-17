#include <string>
#include <winnt.h>
#include <Windows.h>
#include <TlHelp32.h>

void killer(int argc, char **pString);

void killProcessByName(const char *string);

void killProcessById(int id);

int main(int argc, char *argv[]) {
    killer(argc, argv);
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
    HANDLE handle = OpenProcess(PROCESS_TERMINATE, FALSE, id);
    if (handle != nullptr) {
        TerminateProcess(handle, 2);
    }
    CloseHandle(handle);
}

void killProcessByName(const char *string) {
    HANDLE handle =  CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    PROCESSENTRY32 procEntry;
    procEntry.dwSize = sizeof(procEntry);
    BOOL res = Process32First(handle, &procEntry);
    while (res) {
        if (strcmp(procEntry.szExeFile, string) == 0) {
            HANDLE processHandle = OpenProcess(PROCESS_TERMINATE, FALSE, procEntry.th32ProcessID);
            if (processHandle != nullptr) {
                TerminateProcess(processHandle, 2);
            }
            CloseHandle(processHandle);
            res = Process32Next(handle, &procEntry);
        }
    }
}
