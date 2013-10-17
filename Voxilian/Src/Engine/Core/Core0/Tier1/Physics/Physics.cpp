#include "Physics.h"

CPhysics::CPhysics()
{
	collisionconfiguration = nullptr;
	dispatcher = nullptr;
	overlappingpaircache = nullptr;
	solver = nullptr;
}
void CPhysics::Init()
{
	collisionconfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionconfiguration);
	overlappingpaircache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver;
}
void CPhysics::Frame()
{
}
CPhysics Physics;