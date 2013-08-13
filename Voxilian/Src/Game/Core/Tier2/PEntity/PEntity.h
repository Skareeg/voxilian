#ifndef H_PEntity
#define H_PEntity
#include "..\..\Tier1.h"

class CPEntity : public CEntity,public btMotionState
{
public:
	btTransform transform;
	btRigidBody* rigidbody;
	virtual void Init(string newname);
	virtual void SetPhysics(btCollisionShape* collisionshape,float mass);
	virtual void Frame();
	virtual void getWorldTransform(btTransform &worldTrans);
	virtual void setWorldTransform(const btTransform &worldTrans);
};

#endif