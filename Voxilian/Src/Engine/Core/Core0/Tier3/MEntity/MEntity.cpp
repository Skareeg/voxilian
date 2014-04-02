#include "MEntity.h"
CMEntity::CMEntity()
{
	CEntity::CEntity();
	transform.setOrigin(btVector3(0,0,0));
}
CMEntity::CMEntity(btVector3& startposition)
{
	CEntity::CEntity();
	transform.setOrigin(startposition);
}
void CMEntity::Init(string newname)
{
	CEntity::Init(newname);
	SetType("CMEntity");
}
void CMEntity::Update()
{
	CEntity::Update();
}
void CMEntity::Render()
{
	CEntity::Render();
}
bool CMEntity::AddMesh(string filename)
{
	return mesh.AddFile(filename);
}