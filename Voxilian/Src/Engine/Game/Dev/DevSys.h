#ifndef H_DEVSYS
#define H_DEVSYS
#include "..\Core.h"
#include "DevCreators\DevCreators.h"

class CDevSystem
{
public:
	CDevCreator* creationsystem;
	bool devmode;
	bool devmenu;
	vector<string> devinfo;
	void Init();
	void Update();
	void Terminate();
};

extern CDevSystem DevSys;

#endif