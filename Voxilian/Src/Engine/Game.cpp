#include "Game.h"

void buttonend(CWindow* win)
{
	CButton* button = static_cast<CButton*>(win);
	if(button->Activated())
	{
		Graphics.Terminate();
	}
}

CGFlyCam* cam;

void Game::Init()
{
	terminated=false;
	glfwInit();
	Graphics.Init();
	Input.Init();
	Audio.Init(100);
	Physics.Init();
	Graphics.Window(false,640,480);
	//Must call UI Init after Graphics to load textures.
	//UI.Init();
	isRunning=true;
	//CButton* endb = UI.CreateButton(Rect(20,20,128,64),"buttonquitn.png","buttonquith.png","buttonquitp.png");
	//CWindow* endb = UI.CreateWindow(Rect(20,20,64,64,0.5f),"buttonquitn.png");
	//endb->runfunction=buttonend;
	//endb->CreateSounds("error.wav","spawn.wav","startup.wav");
	FMOD::Sound* startsn = Audio.CreateSound("iniated.wav");
	if(Audio.fresult!=FMOD_OK)
	{
		Log.Log("Fmod startup sound problem.",0);
	}
	else
	{
		Audio.PlaySound(startsn);
	}
	DevSys.Init();

	sc_MainMenu = SceneMgr.CreateScene("MainMenu");
	sc_GameWorld = SceneMgr.CreateScene("GameWorld");
	sc_MainMenu->Init();
	sc_GameWorld->Init();
	SceneMgr.SetScene(sc_MainMenu);

	CGMenu* menu = new CGMenu();
	sc_MainMenu->Add(menu);
	menu->Init("MainMenu");

	cam = new CGFlyCam();
	cam->Init("GameCam");
	Graphics.SetCamera(cam->camera);
	cam->camera->position = btVector3(0,0,-5);
	sc_GameWorld->Add(cam);
	cam->UI->UICreateWindow(Rect(0,0,64,64),"buttonstarth.png");
	cam->UI->EnableSystem();
}

void Game::Run()
{
	isRunning = (!Input.GetKeyDown(GLFW_KEY_ESC)&&glfwGetWindowParam(GLFW_OPENED));
	Graphics.Begin();
	Input.Update((Graphics.resolution_x/2.0f),(Graphics.resolution_y/2.0f));
	Crosshair.Update();
	SceneMgr.Update();
	Audio.Update();
	DevSys.Update();

	string st = "FPS:->";
	Graphics.Text.DrawText(0,0,0.25f,st+str((1.0f/Graphics.deltaTime)));

	Graphics.Draw.DrawCube(btVector3(0,0,25),3.0f);

	glBindTexture(GL_TEXTURE_2D,0);
	glBegin(GL_TRIANGLES);
	glColor3f(1,1,1);
	glVertex3f(0,0,0);
	glVertex3f(2,0,0);
	glVertex3f(2,5,0);
	glEnd();

	Graphics.End();

	Log.Send();
}

void Game::Terminate()
{
	if(!terminated)
	{
		Input.Terminate();
		Graphics.Terminate();
		terminated=true;
	}
}