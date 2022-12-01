#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::string string;
    std::getline(std::cin, string);
    std::stringstream ss(string);
    int x;
    while (ss >> x) {
        std::cout << x + 15 << " ";
    }
    std::cout << "\n";
    return 0;
}
