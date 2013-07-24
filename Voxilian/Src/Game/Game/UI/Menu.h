#ifndef H_GMENU
#define H_GMENU
#include "..\..\Core\Globals.h"
#include "..\..\Core\Tier1.h"
#include "..\..\Core\Tier2.h"

class CGMenu : CEntity
{
public:
	UITex t_startn;
	UITex t_starth;
	UITex t_startp;
	UITex t_quitn;
	UITex t_quith;
	UITex t_quitp;
	virtual void Init(string newname);
	virtual void Frame();
};

#endif