#pragma once

#ifdef VECTOR_Export
#define DllExport __declspec(dllexport)+
#else
#define DllExport __declspec(dllimport)
#endif

#pragma comment(lib, "C:\\Users\\Dima\\source\\repos\\Number\\x64\\Debug\\Number")

#include "C:\\Users\\Dima\\source\\repos\\Number\\Number\\Number.h"

# define M_PI           3.14159265358979323846


	class __declspec(dllimport) Vector {
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
		extern const  __declspec(dllimport) Vector ONE_ONE;
		extern const Vector ZERO_ZERO;
	}
