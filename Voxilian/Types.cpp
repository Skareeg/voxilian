#include "Types.h"

namespace VMath
{
	float Distance(Vector3 v1,Vector3 v2)
	{
		float np;
		np=sqrtf(powf((v2.x-v1.x),2.0f)+powf((v2.y-v1.y),2.0f));
		np=sqrtf(powf(np,2.0f)+powf((v2.z-v1.z),2.0f));
		return np;
	}
	Vector3 Vector(float x,float y,float z)
	{
		Vector3 nv;
		nv.x=x;
		nv.y=y;
		nv.z=z;
		return nv;
	}
}