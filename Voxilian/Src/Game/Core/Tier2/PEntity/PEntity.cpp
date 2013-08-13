#include "PEntity.h"
void CPEntity::Init(string newname)
{
	CEntity::Init(newname);
	SetType("CPEntity");
}
void CPEntity::SetPhysics(btCollisionShape* collisionshape,float mass)
{
	collisionshape->calculateLocalInertia(mass,btVector3(0,0,0));
	rigidbody = new btRigidBody(mass,this,collisionshape,btVector3(0,0,0));
}
void CPEntity::Frame()
{
}
void CPEntity::getWorldTransform(btTransform &worldTrans)
{
	worldTrans=transform;
}
void CPEntity::setWorldTransform(const btTransform &worldTrans)
{
	transform=worldTrans;
}