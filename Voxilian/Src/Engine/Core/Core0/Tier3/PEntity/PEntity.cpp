#include "PEntity.h"
CPEntity::CPEntity()
{
	CEntity::CEntity();
	motionstate = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	transform=btTransform();
	transform.setOrigin(btVector3(0,0,0));
}
CPEntity::CPEntity(btVector3& startposition)
{
	CEntity::CEntity();
	motionstate = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),startposition));
	transform=btTransform();
	transform.setOrigin(startposition);
}
void CPEntity::Init(string newname)
{
	CEntity::Init(newname);
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
void CPEntity::Frame()
{
	CEntity::Frame();
	motionstate->getWorldTransform(transform);
}