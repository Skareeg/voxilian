#include "DevSys.h"

void CDevSystem::Init()
{
	creationsystem = new CDevCreator();
	creationsystem->Init(this);
	devmode=false;
	devmenu=false;
}
void CDevSystem::Update()
{
	if(Input.GetKeyPressed('~')==true)
	{
		devmode=!devmode;
	}
	creationsystem->Frame();
	if(devmode)
	{
		if(Input.GetKeyPressed(GLFW_KEY_F1)==true)
		{
			devmenu=!devmenu;
		}
		devinfo.push_back("Press F1 for devmenu.");
		devinfo.push_back("Current scene name: "+SceneMgr.curscene->name+".");
		devinfo.push_back("Current scene # elements: "+str(SceneMgr.curscene->elements.size())+".");
		for(unsigned int i = 0;i<devinfo.size();i++)
		{
			Graphics.Text.DrawTextW(0,i*14,-1,devinfo[i]);
		}
	}
}
void CDevSystem::Terminate()
{
	creationsystem->Terminate();
	delete creationsystem;
}
CDevSystem DevSys;