#include "Entity.h"
#include "..\..\Core0.h"

CEntity::CEntity()
{
	root=nullptr;
	parent=nullptr;
}
void CEntity::RegisterCurrent()
{
	SceneMgr.curscene->Add(this);
}
void CEntity::Init(string newname)
{
	UI = new CUI();
	name=newname;
	SetType("CEntity");
}
void CEntity::Frame()
{
	UI->Update();
	for(int i = 0;i<elements.size();i++)
	{
		elements[i]->Frame();
	}
}
void CEntity::Terminate()
{
	delete UI;
}
void CEntity::SetType(string newtype)
{
	type=newtype;
	types.push_back(newtype);
}
bool CEntity::HasType(string hastype)
{
	int sz = types.size();
	for(int i = 0;i<sz;i++)
	{
		if(types[i]==hastype)
		{
			return true;
		}
	}
	return false;
}
void CEntity::AddCommand(string cmd)
{
	commands.push_back(cmd);
}