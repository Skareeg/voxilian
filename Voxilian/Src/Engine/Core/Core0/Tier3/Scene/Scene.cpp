#include "Scene.h"
#include "..\..\Core0.h"

CScene::CScene()
{
	name="";
}

void CScene::Init()
{
	btworld = new btDiscreteDynamicsWorld(Physics.dispatcher,Physics.overlappingpaircache,Physics.solver,Physics.collisionconfiguration);
	btworld->setGravity(btVector3(0,0,0));
}

void CScene::Add(CEntity* element)
{
	element->root=this;
	elements.push_back(element);
}

void CScene::Add(CEntity* e1,CEntity* e2)
{
	e1->root=this;
	e1->parent=e2;
	e2->root=this;
	e2->elements.push_back(e1);
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
void CScene::Update()
{
	btworld->stepSimulation(Graphics.deltaTime,10);
}
void CScene::Render()
{
	for(unsigned int i = 0;i<elements.size();i++)
	{
		elements[i]->Render();
	}
}

void CManager::SetScene(CScene* setscene)
{
	string prevsc = "NA";
	if(curscene!=nullptr)
	{
		prevsc=curscene->name;
	}
	curscene=setscene;
	Log.Log("Scene has changed: "+prevsc+"->"+curscene->name+";",0);
}
void CManager::SetScene(string scenename)
{
	for(unsigned int i = 0;i<scenes.size();i++)
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
	curscene->Update();
	for(unsigned int i = 0;i<curscene->elements.size();i++)
	{
		curscene->elements[i]->Update();
	}
}
void CManager::Render()
{
	curscene->Render();
}

CManager SceneMgr;