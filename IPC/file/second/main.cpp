#include <iostream>
#include <fstream>

int main()
{
    int state = 1;
    while (state) {
        std::cin >> state;
        if (state > 2 || state < 0) {
            std::cout << "Wrong state";
            return 1;
        }
        if (state == 1) {
            int num;
            std::cin >> num;
            std::ofstream out("..//..//file");
            out << "2" << "\n";
            out << num;
            out.close();
        }
        if (state == 2) {
            std::ifstream in("..//..//file");
            int buf = 0;
            in >> buf;
            if (buf == 1) {
                in >> buf;
                std::cout << buf << "\n";
            }
            else {
                std::cout << "Nothing to recieve\n";
            }
            in.close();
        }
    }
}