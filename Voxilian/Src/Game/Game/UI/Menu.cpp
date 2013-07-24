#include "Menu.h"

void CGMenu::Init(string newname)
{
	CEntity::Init(newname);
	SetType("CGMenu");
	t_startn=Graphics.LoadTexture("UI\\Menu\\startn.png",false);
	t_starth=Graphics.LoadTexture("UI\\Menu\\starth.png",false);
	t_startp=Graphics.LoadTexture("UI\\Menu\\startp.png",false);
	t_quitn=Graphics.LoadTexture("UI\\Menu\\quitn.png",false);
	t_quith=Graphics.LoadTexture("UI\\Menu\\quith.png",false);
	t_quitp=Graphics.LoadTexture("UI\\Menu\\quitp.png",false);
}

void CGMenu::Frame()
{
	CEntity::Frame();
}