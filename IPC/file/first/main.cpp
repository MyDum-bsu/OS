#include <iostream>
#include <fstream>

int main() {
    int state = 1;
    while (state) {
        std::cin >> state;
        switch(state) {
            case 1: {
                int num;
                std::cin >> num;
                std::ofstream out("..//..//file");
                out << "1" << "\n";
                out << num;
                out.close();
                break;
            }
            case 2: {
                std::ifstream in("..//..//file");
                int buf = 0;
                in >> buf;
                if (buf == 2) {
                    in >> buf;
                    std::cout << buf << "\n";
                } else {
                    std::cout << "Nothing to recieve\n";
                }
                in.close();
                break;
            }
            default: {
                std::cout << "Wrong state";
                return 1;
            }
        }
    }
}