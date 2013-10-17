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
	bool isInit;
	string name;
	string type;
	vector<CVar> vars;
	vector<string> types;
	vector<CEntity*> elements;
	CScene* root;
	CEntity* parent;
	CUI* UI;
	FMOD::Channel* sn_ch_Main;
	vector<string> commands;
	CEntity();
	virtual void RegisterCurrent();
	virtual void Init(string newname);
	virtual void Frame();
	virtual void Terminate();
	virtual void SetType(string newtype);
	virtual void AddCommand(string cmd);
	bool HasType(string hastype);
};

#endif