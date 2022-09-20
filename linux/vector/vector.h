#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include "number.h"

class Vector {
public:
    Vector(Number x, Number y);

    Vector(const Vector&) = default;

    double getAngle();

    double getRadius();

    Vector addVector(Vector& v);

    Number getX();

    Number getY();
private:
    Number x_;
    Number y_;
};
namespace vectorConstants {
    extern const Vector ONE_ONE;
    extern const Vector ZERO_ZERO;
}

#endif //VECTOR_VECTOR_H
