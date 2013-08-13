#include "Physics.h"

CPhysics::CPhysics()
{
	collisionconfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionconfiguration);
	overlappingpaircache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver;
}
void CPhysics::Init()
{
}
void CPhysics::Frame()
{
}
CPhysics Physics;