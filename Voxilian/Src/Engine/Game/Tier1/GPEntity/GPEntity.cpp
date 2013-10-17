#include "GPEntity.h"

CGPEntity::CGPEntity()
{
	CPEntity::CPEntity();
}
CGPEntity::CGPEntity(btVector3& startposition)
{
	CPEntity::CPEntity(startposition);
}
void CGPEntity::Init(string newname)
{
	CPEntity::Init(newname);
	SetType("CGPEntity");
}
void CGPEntity::Frame()
{
}
void CGPEntity::Terminate()
{
}