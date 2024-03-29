#include "Entity.h"
#include "..\..\Core0.h"

CEntity::CEntity()
{
	isInit=false;
	name="";
	type="";
	root=nullptr;
	parent=nullptr;
	sn_ch_Main=nullptr;
}
void CEntity::RegisterCurrent()
{
	SceneMgr.curscene->Add(this);
}
void CEntity::Init(string newname)
{
	name=newname;
	SetType("CEntity");
}
void CEntity::Update()
{
	for(int i = 0;i<elements.size();i++)
	{
		elements[i]->Update();
	}
}
void CEntity::Render()
{
	for(int i = 0;i<elements.size();i++)
	{
		elements[i]->Render();
	}
}
void CEntity::Terminate()
{
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