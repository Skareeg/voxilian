#ifndef H_PEntity
#define H_PEntity
#include "..\..\Tier1\Tier1.h"

class CPEntity : public CEntity
{
public:
	btTransform transform;
	btDefaultMotionState* motionstate;
	btRigidBody* rigidbody;
	CPEntity();
	CPEntity(btVector3& startposition);
	virtual void Init(string newname);
	virtual void SetPhysics(btCollisionShape* collisionshape,float mass);
	virtual void Frame();
};

#endif