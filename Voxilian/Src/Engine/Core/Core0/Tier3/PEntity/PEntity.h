#ifndef H_PEntity
#define H_PEntity
#include "..\..\Tier1\Tier1.h"
#include "..\MEntity\MEntity.h"

class CPEntity : public CMEntity
{
public:
	btDefaultMotionState* motionstate;
	btRigidBody* rigidbody;
	CPEntity();
	CPEntity(btVector3& startposition);
	virtual void Init(string newname);
	virtual void SetPhysics(btCollisionShape* collisionshape,float mass);
	virtual void Update();
	virtual void Render();
};

#endif