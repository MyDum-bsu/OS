#include "vector.h"
#include <cmath>
# define M_PI           3.14159265358979323846

Vector::Vector(Number x, Number y) : x_(x), y_(y) {}

double Vector::getRadius() {
    return sqrt(x_.multiplyNumber(x_).getValue() + y_.multiplyNumber(y_).getValue());
}

Number Vector::getX() {
    return x_;
}

Number Vector::getY() {
    return y_;
}

Vector Vector::addVector(Vector& v) {
    return Vector(x_.addNumber(v.getX()), y_.addNumber(v.getY()));
}

double Vector::getAngle() {
    double angle = atan(y_.divideNumber(x_).getValue());
    if (x_.getValue() >= constants::ZERO.getValue()) {
        return angle;
    }
    if (y_.getValue() >= constants::ZERO.getValue()) {
        return M_PI - angle;
    }
    return M_PI + angle;
}

namespace vectorConstants {
    const Vector ZERO_ZERO = Vector(constants::ZERO, constants::ZERO);
    const Vector ONE_ONE = Vector(constants::ONE, constants::ONE);
}
