#include "PEntity.h"
CPEntity::CPEntity()
{
	CMEntity::CMEntity();
	motionstate = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
}
CPEntity::CPEntity(btVector3& startposition)
{
	CMEntity::CMEntity(startposition);
	motionstate = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),startposition));
}
void CPEntity::Init(string newname)
{
	CMEntity::Init(newname);
	SetType("CPEntity");
}
void CPEntity::SetPhysics(btCollisionShape* collisionshape,float mass)
{
	btVector3 inertia = btVector3(0,0,0);
	collisionshape->calculateLocalInertia(mass,inertia);
	btRigidBody::btRigidBodyConstructionInfo info(mass,motionstate,collisionshape,inertia);
	rigidbody = new btRigidBody(info);
	rigidbody->activate(true);
}
void CPEntity::Update()
{
	CMEntity::Update();
	motionstate->getWorldTransform(transform);
}
void CPEntity::Render()
{
	CMEntity::Render();
}