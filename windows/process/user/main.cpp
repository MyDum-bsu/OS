#include <iostream>
#include <windows.h>
#include <utility>
#include <vector>
#include <tlhelp32.h>
#include <algorithm>
#include <string>

const std::string PATH_TO_KILLER = "../../killer/cmake-build-debug/killer.exe";

struct Process {
    DWORD id;
    std::string name;

    Process(DWORD handle, std::string name) : id(handle), name(std::move(name)) {}

    bool operator==(const Process &rhs) const {
        return name == rhs.name;
    }

    bool operator!=(const Process &rhs) const {
        return !(rhs == *this);
    }
};

std::vector<Process> getActiveProcesses() {
    std::vector<Process> result;
    HANDLE process_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (process_snap == INVALID_HANDLE_VALUE) {
        return result;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    bool proc = Process32First(process_snap, &pe32);
    while (proc) {
        result.emplace_back(pe32.th32ProcessID, std::string(pe32.szExeFile));
        proc = Process32Next(process_snap, &pe32);
    }
    CloseHandle(process_snap);
    return result;
}

bool isRunning(DWORD id) {
    auto processes = getActiveProcesses();
    return std::any_of(processes.begin(), processes.end(), [&](const Process &p) {
        return p.id == id;
    });
}

void printInfo(const std::vector<Process> &processes) {
    for (auto &process: processes) {
        std::cout << "Process [" << process.id << "] " << process.name << " is " << (isRunning(process.id)
                                                                                     ? "running"
                                                                                     : "stopped");
        std::cout << std::endl;
    }
}

std::vector<Process> match(const std::vector<std::string> &names,
                           const std::vector<std::string> &from_var,
                           const std::vector<Process> &processes) {
    std::vector<Process> result;
    for (auto &p: processes) {
        if (std::any_of(names.begin(), names.end(), [&](const std::string &s) {
            return s == p.name;
        }) || std::any_of(from_var.begin(), from_var.end(), [&](const std::string &s) {
            return s == p.name;
        })) {
            result.emplace_back(p);
        }
    }
    return result;
}

void killProcesses(const std::vector<Process> &processes) {
    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION process_information;
    const int BUFF_SIZE = 500;
    char buff[BUFF_SIZE];
    std::string joined = PATH_TO_KILLER + " --id";
    for (auto &proc: processes) {
        joined += " " + std::to_string(proc.id);
    }
    strcpy_s(buff, BUFF_SIZE, joined.c_str());
    CreateProcess(nullptr, buff, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &process_information);
    WaitForSingleObject(process_information.hThread, INFINITE);
    CloseHandle(process_information.hThread);
    WaitForSingleObject(process_information.hProcess, INFINITE);
    CloseHandle(process_information.hProcess);
}

int main() {
    SetEnvironmentVariableA("PROC_TO_KILL", "Telegram.exe");
    std::vector<std::string> processes = {"Telegram.exe"};
    auto processes_p = match(processes, {"Telegram.exe"}, getActiveProcesses());
    if (processes_p.empty()) {
        std::cout << "nothing to kill" << std::endl;
        return 0;
    }
    printInfo(processes_p);
    killProcesses(processes_p);
    printInfo(processes_p);
    return 0;
}