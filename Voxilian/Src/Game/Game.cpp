#include "Game.h"

void Game::Init()
{
	//The game has not terminated.
	terminated=false;

	//Init glfw and the Graphics API.
	glfwInit();
	Graphics.Init();
	Graphics.Window(false,640,480);

	//Init the Audio with 100 channels, Physics, and Input with the default crosshair lock.
	Audio.Init(100);
	Physics.Init();
	Input.Init((Graphics.resolution_x/2.0f),(Graphics.resolution_y/2.0f));

	//UI Init here.
	UI.Init();

	//Init Dev after UI.
	//DevUI.Init();

	//Perform startup procedures.
	isRunning=true;
	FMOD::Sound* startsn = Audio.CreateSound("iniated.wav");
	if(Audio.fresult!=FMOD_OK)
	{
		Log.Log("Fmod startup sound problem.",0);
	}
	else
	{
		Audio.PlaySound(startsn);
	}

	//Create and Init The Main Menu and The Game World.
	sc_MainMenu = SceneMgr.CreateScene("MainMenu");
	sc_GameWorld = SceneMgr.CreateScene("GameWorld");
	sc_MainMenu->Init();
	sc_GameWorld->Init();
	SceneMgr.SetScene(sc_MainMenu);

	CMEntity* latiasmesh = new CMEntity(btVector3(0,0,50));
	if(!latiasmesh->AddMesh("Static\\latias.obj"))
	{
		Log.Log("ERROR! CANNOT OPEN LATIAS MESH!",0);
		system("pause");
		exit(1);
	}
}

void Game::Run()
{
	//Update All Systems.
	{
		isRunning = (!Input.GetKeyDown(GLFW_KEY_ESC)&&glfwGetWindowParam(GLFW_OPENED));
		Input.Update();
		SceneMgr.Update();
		Audio.Update();
		UI.Update();
	}

	//Update global input
	if(Input.GetKeyPressed('`'))
	{
		//DevUI.Toggle();
	}
	if(Input.GetKeyPressed(GLFW_KEY_TAB))
	{
		UI.CursorToggle();
	}

	//Render all objects
	{
		Graphics.Begin();

		string st = "FPS:->";
		Graphics.Text.Draw(0.0f,0.0f,0.25f,st+str((1.0f/Graphics.deltaTime)));

		Graphics.Draw.DrawCube(btVector3(0,0,25),3.0f);

		glBindTexture(GL_TEXTURE_2D,0);
		glBegin(GL_TRIANGLES);
		glColor3f(1,1,1);
		glVertex3f(0,0,0);
		glVertex3f(2,0,0);
		glVertex3f(2,5,0);
		glEnd();
	
		SceneMgr.Render();
		UI.Render();

		Graphics.End();
	}

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