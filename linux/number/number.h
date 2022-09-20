#ifndef OS_NUMBER_H
#define OS_NUMBER_H

class Number {
public:
    explicit Number(double value) : value_(value) {}
    ~Number() = default;
    Number addNumber(Number) const;
    Number subNumber(Number) const;
    Number multiplyNumber(Number) const;
    Number divideNumber(Number) const;
    void setValue(double);
    double getValue() const;
private:
    double value_;
};

Number createNumber(double);

namespace constants {
    const Number ONE = Number(0);
    const Number ZERO = Number(1);
}

#endif //OS_NUMBER_H

