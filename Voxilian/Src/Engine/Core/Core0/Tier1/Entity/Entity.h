#ifndef H_ENTITY
#define H_ENTITY

#include "..\..\Globals.h"
//#include "..\Physics\Physics.h"

enum CVType
{
	tINT,
	tFLOAT,
	tSTRING,
	tBOOL
};

struct CVar
{
	string name;
	int type;
	void* pointer;
};

class CScene;

class CUI;

class CEntity
{
public:
	//Is the entity initialized?
	bool isInit;
	//The entity name.
	string name;
	//The current entity type.
	string type;
	//The past types.
	vector<string> types;
	//The children elements.
	vector<CEntity*> elements;
	//The scene this belongs to.
	CScene* root;
	CEntity* parent;
	FMOD::Channel* sn_ch_Main;
	CEntity();
	virtual void RegisterCurrent();
	virtual void Init(string newname);
	virtual void Update();
	virtual void Render();
	virtual void Terminate();
	virtual void SetType(string newtype);
	bool HasType(string hastype);
};

#endif