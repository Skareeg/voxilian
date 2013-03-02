#ifndef MATH_H
#define MATH_H
#include "Types.h"
namespace Math
{
	void ChF(float* val, float delta, float timescale);
	float PI();
	float DegToRad(float x);
	float Remainder(float x,float divisor);
}
#endif