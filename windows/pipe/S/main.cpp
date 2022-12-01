#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::string string;
    std::getline(std::cin, string);
    std::stringstream ss(string);
    int sum = 0;
    int x;
    while (ss >> x) {
        sum += x;
    }
    std::cout << sum << "\n";
    return 0;
}
