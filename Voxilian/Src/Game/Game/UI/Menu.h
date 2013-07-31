#ifndef H_GMENU
#define H_GMENU
#include "..\..\Core\Globals.h"
#include "..\..\Core\Tier1.h"
#include "..\..\Core\Tier2.h"

class CGMenu : public CEntity
{
public:
	CButton* btn_start;
	CButton* btn_quit;
	CGMenu();
	virtual void Init(string newname);
	virtual void Frame();
};

#endif