#include <iostream>

#include "../vector/vector.h"

int main()
{
    Number x(10);
    Number y(6);

    std::cout << "x = " << x.getValue() << "\n";
    std::cout << "y = " << y.getValue() << "\n";

    x = x.addNumber(y);
    std::cout << "x + y = " << x.getValue() << "\n";

    x = x.subNumber(y);
    x = x.subNumber(y); // (x + y) - y - y = x - y
    std::cout << "x - y = " << x.getValue() << "\n";

    Vector a (Number(2), Number(7));

    std::cout << "a = (" << a.getX().getValue() << "," << a.getY().getValue() << ")\n";

    std::cout << "a_angle = " << a.getAngle() << "\n" << "a_radius = " << a.getRadius() << "\n";

    Vector b (Number(2), Number(4));

    std::cout << "b = (" << b.getX().getValue() << "," << b.getY().getValue() << ")\n";

    a = a.addVector(b);
    std::cout << "a + b = (" << a.getX().getValue() << "," << a.getY().getValue() << ")\n";
    return 0;
}
