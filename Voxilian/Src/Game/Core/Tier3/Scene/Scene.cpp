#include "Scene.h"
#include "..\..\Core.h"

CScene::CScene()
{
}

void CScene::Init()
{
}

void CScene::Add(CEntity* element)
{
	element->root=this;
	elements.push_back(element);
}

void CScene::Add(CEntity* e1,CEntity* e2)
{
	e1->root=this;
	e2->root=this;
	e1->elements.push_back(e2);
}

CManager::CManager()
{
	curscene=nullptr;
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
	string prevsc = "NA";
	if(curscene!=nullptr)
	{
		prevsc=curscene->name;
	}
	curscene=setscene;
	Log.Log("Scene has changed---"+prevsc+"->"+curscene->name+";",0);
}
void CManager::SetScene(string scenename)
{
	for(int i = 0;i<scenes.size();i++)
	{
		if(scenes[i]->name==scenename)
		{
			string prevsc = "NA";
			if(curscene!=nullptr)
			{
				prevsc=curscene->name;
			}
			curscene=scenes[i];
			Log.Log("Scene has changed---"+prevsc+"->"+curscene->name+";",0);
			return;
		}
	}
	Log.Log("NO SUCH SCENE --- "+scenename,0);
}
void CManager::Update()
{
	for(int i = 0;i<curscene->elements.size();i++)
	{
		curscene->elements[i]->Frame();
	}
}

CManager SceneMgr;