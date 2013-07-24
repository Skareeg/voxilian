#include "Game.h"
CButton* button;
void buttonend(CWindow* win)
{
	button = static_cast<CButton*>(win);
	if(button->Activated())
	{
		Graphics.Terminate();
	}
}

void Game::Init()
{
	glfwInit();
	Graphics.Init();
	Input.Init();
	Audio.Init(100);
	Graphics.Window(false,640,480);
	//Must call UI Init after Graphics to load textures.
	UI.Init();
	isRunning=true;
	CButton* endb = UI.CreateButton(Rect(20,20,128,64),"buttonquitn.png","buttonquith.png","buttonquitp.png");
	//CWindow* endb = UI.CreateWindow(Rect(20,20,64,64,0.5f),"buttonquitn.png");
	endb->runfunction=buttonend;
	endb->CreateSounds("Sounds\\error.wav","Sounds\\spawn.wav","Sounds\\startup.wav");
	FMOD::Sound* startsn = Audio.CreateSound("Sounds\\iniated.wav");
	if(Audio.fresult!=FMOD_OK)
	{
		Log.Log("Fmod startup sound problem.",0);
	}
	else
	{
		Audio.PlaySound(startsn);
	}
	sc_MainMenu = SceneMgr.CreateScene("MainMenu");
	sc_GameWorld = SceneMgr.CreateScene("GameWorld");
	SceneMgr.SetScene(sc_MainMenu);
}

void Game::Run()
{
	isRunning = (!Input.GetKey(GLFW_KEY_ESC)&&glfwGetWindowParam(GLFW_OPENED));
	Graphics.Begin();
	Input.Update(UI.cursorLock,(Graphics.resolution_x/2.0f),(Graphics.resolution_y/2.0f));
	UI.Update();
	Audio.Update();
	SceneMgr.Update();
	Graphics.Text.DrawText(0,0,0.25f,"Hahahahahaa!!! I am super ninja!");
	Graphics.End();
}

void Game::Terminate()
{
	Input.Terminate();
	Graphics.Terminate();
}