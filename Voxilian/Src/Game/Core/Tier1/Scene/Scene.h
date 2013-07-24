#ifndef H_SCENE
#define H_SCENE
#include "..\..\Globals.h"

class CEntity
{
public:
	string name;
	string type;
	vector<string> types;
	vector<CEntity*> elements;
	btVector3 position;
	btQuaternion rotation;
	btVector3 origin;
	CEntity();
	virtual void RegisterCurrent();
	virtual void Init(string newname);
	virtual void Frame();
	virtual void Terminate();
	virtual void SetType(string newtype);
	bool HasType(string hastype);
};

class CScene
{
public:
	string name;
	vector<CEntity*> elements;
	void Add(CEntity* element);
};

class CManager
{
public:
	CScene* curscene;
	vector<CScene*> scenes;
	CScene* CreateScene(string name);
	void SetScene(CScene* setscene);
	void DrawScene();
};

extern CManager SceneMgr;

#endif