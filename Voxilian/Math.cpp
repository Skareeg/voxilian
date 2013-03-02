#include "Math.h"
void Math::ChF(float* val, float delta, float timescale)
{
	(*val)+=(delta*(timescale));
}
float Math::PI()
{
	return 3.14159265359f;
}
float Math::DegToRad(float x)
{
	return x*(PI()/180.0f);
}
float Math::Remainder(float x,float divisor)
{
	float r = x;
	float divided = x/divisor;
	float intdivided = (float)(int)(divided);
	float subtracted = divided-intdivided;
	float remainder = subtracted * divisor;
	r=remainder;
	return r;
}