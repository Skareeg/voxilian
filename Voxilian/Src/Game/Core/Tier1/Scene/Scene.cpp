#include "Scene.h"

CEntity::CEntity()
{
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
void CEntity::Frame()
{
	for(int i = 0;i<elements.size();i++)
	{
		elements[i]->Frame();
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

void CScene::Add(CEntity* element)
{
	elements.push_back(element);
}

CScene* CManager::CreateScene(string name)
{
	CScene* s = new CScene();
	s->name=name;
	scenes.push_back(s);
	return s;
}
void CManager::SetScene(CScene* setscene)
{
	curscene=setscene;
}
void CManager::Update()
{
	for(int i = 0;i<curscene->elements.size();i++)
	{
		curscene->elements[i]->Frame();
	}
}

CManager SceneMgr;