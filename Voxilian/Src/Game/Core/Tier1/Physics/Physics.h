#ifndef H_PHYSICS
#define H_PHYSICS
#include "..\..\Globals.h"

class CPhysics
{
public:
	btDefaultCollisionConfiguration* collisionconfiguration;
	btBroadphaseInterface* overlappingpaircache;
	btSequentialImpulseConstraintSolver* solver;
	btCollisionDispatcher* dispatcher;
	CPhysics();
	void Init();
	void Frame();
};
extern CPhysics Physics;

#endif