#ifndef H_UI
#define H_UI
#include "..\..\Globals.h"
#include "..\..\Tier1.h"

class CUI
{
public:
	CEGUI::OpenGLRenderer* rend;
	CUI();
	void Init();
	void Draw();
};
extern CUI UI;

#endif