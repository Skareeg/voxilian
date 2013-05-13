#include "Game.h"
#include "Thread\tinythread.h"
#include <thread>
void Game::Init()
{
	//Initialize the drawing system, initialize the voxelmanager and its voxels, and create a window. (Window(false)).
	glS.Init();
	m.Init(&glS.camera->pos);
	glS.Window(false);
}
void Game::Render()
{
	//Draw from camera.
	glS.DrawBegin();
	//Draw a double sided reference triangle.
	glBegin(GL_TRIANGLES);
	glColor3f(0.5f,0.5f,0.5f);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);
	glVertex3f(1,0,0);
	glVertex3f(1,0,0);
	glVertex3f(0,1,0);
	glVertex3f(0,0,0);
	glEnd();
	m.Render();
	//Draw voxelmanager and its associated voxels.
	//voxelmanager.Render();
	//End the camera drawing system. (swaps the buffers)
	glS.DrawEnd();
}
void Game::Run()
{
	//Get camera position and update the voxelmanager with it.
	Vector3 v;
	v=glS.camera->pos;
	v.x=v.x;
	v.y=v.y;
	v.z=v.z;
	glS.FlyInput();
	if(glS.GetKey('R')==true)
	{
		//voxelmanager.VDSphere(v,1,-0.1f,true);
	}
	//glS.Run is always called last. (timescaling/mousemovement)
	glS.Run();
	g_cmd.DeleteNextCalls();
}
void Game::End()
{
	//Terminate the drawing system. (closes window and terminates glfw)
	glS.Terminate();
}