#include "Menu.h"
#include "..\..\..\Core\Core.h"

void startfunc(CWindow* win)
{
	CButton* button = static_cast<CButton*>(win);
	if(button->Activated())
	{
		Crosshair.enabledcrosshair=false;
		SceneMgr.SetScene("GameWorld");
	}
}
void quitfunc(CWindow* win)
{
	CButton* button = static_cast<CButton*>(win);
	if(button->Activated())
	{
		Crosshair.enabledcrosshair=false;
		Graphics.Terminate();
	}
}

CGMenu::CGMenu()
{
	CEntity::CEntity();
}
void CGMenu::Init(string newname)
{
	CEntity::Init(newname);
	SetType("CGMenu");
	float rx = Graphics.resolution_x;
	float ry = Graphics.resolution_y;
	float px = rx/2.0f;
	float py = ry/2.0f;
	btn_start = UI->UICreateButton(Rect(px-64,py-16,128,32),
		"buttonstartn.png",
		"buttonstarth.png",
		"buttonstartp.png");
	btn_quit = UI->UICreateButton(Rect(px-64,py+32,128,32),
		"buttonquitn.png",
		"buttonquith.png",
		"buttonquitp.png");
	btn_start->runfunction=startfunc;
	btn_quit->runfunction=quitfunc;
	UI->EnableSystem();
	UI->EnableCrossHair("crosshair.png");
}

void CGMenu::Frame()
{
	CEntity::Frame();
	if(Input.GetKeyPressed('F')==true)
	{
		Input.lockmouse=!Input.lockmouse;
		Crosshair.enabledcrosshair=!Input.lockmouse;
	}
}