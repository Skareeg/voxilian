#ifndef H_SCENE
#define H_SCENE

#include "..\..\Globals.h"
#include "..\..\Tier1.h"
#include "..\..\Tier2.h"

class CScene
{
public:
	string name;
	vector<CEntity*> elements;
	CScene();
	void Init();
	void Add(CEntity* element);
	void Add(CEntity* e1,CEntity* e2);
};

class CManager
{
public:
	CScene* curscene;
	vector<CScene*> scenes;
	CManager();
	CScene* CreateScene(string name);
	void SetScene(CScene* setscene);
	void SetScene(string scenename);
	void Update();
};

extern CManager SceneMgr;

#endif