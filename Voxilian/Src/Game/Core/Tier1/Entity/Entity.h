#ifndef H_ENTITY
#define H_ENTITY

#include "..\..\Globals.h"
//#include "..\Physics\Physics.h"

class CScene;

class CUI;

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
	CScene* root;
	CEntity* parent;
	CUI* UI;
	CEntity();
	virtual void RegisterCurrent();
	virtual void Init(string newname);
	virtual void Frame();
	virtual void Terminate();
	virtual void SetType(string newtype);
	bool HasType(string hastype);
};

#endif