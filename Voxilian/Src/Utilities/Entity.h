#ifndef ENT_H
#define ENT_H
#include "Types.h"
class Entity
{
public:
	Vector3 pos;
	Vector3 rot;
	Entity* parent;
};
#endif