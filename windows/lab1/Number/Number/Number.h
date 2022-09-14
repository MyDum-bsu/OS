#pragma once

#include "pch.h"
#include "framework.h"


class Number {
public:
	Number(double value) : value_(value) {}
	~Number() = default;
	Number addNumber(Number);
	Number subNumber(Number);
	Number multiplyNumber(Number);
	Number divideNumber(Number);
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
