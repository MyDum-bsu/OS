#include "number.h"

Number Number::addNumber(Number a) const {
    return Number(value_ + a.value_);
}

Number Number::subNumber(Number a) const {
    return Number(value_ - a.value_);
}

Number Number::multiplyNumber(Number a) const {
    return Number(value_ * a.value_);
}

Number Number::divideNumber(Number a) const {
    return Number(value_ / a.value_);
}

void Number::setValue(double value) {
    value_ = value;
}

Number createNumber(double value) {
    return Number(value);
}

double Number::getValue() const{
    return value_;
}
