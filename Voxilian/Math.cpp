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