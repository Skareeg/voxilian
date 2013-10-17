#ifndef H_GENTITY
#define H_GENTITY
#include "..\..\..\Core\Core.h"

class CGEntity : public CEntity
{
public:
	CGEntity();
	virtual void Init(string newname);
	virtual void Frame();
	virtual void Terminate();
};

#endif