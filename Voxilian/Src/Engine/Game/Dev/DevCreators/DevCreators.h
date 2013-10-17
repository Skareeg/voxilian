#ifndef H_DEVCREATORS
#define H_DEVCREATORS
#include "DCCEnt\DCCEnt.h"

class CDevSystem;

class CDevCreator
{
public:
	CDevSystem* devsystem;
	bool devmode;
	void Init(CDevSystem* devsys);
	void Frame();
	void Terminate();
};

#endif