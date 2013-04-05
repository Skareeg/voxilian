#include "Game.h"
void Game::Init()
{
	//Initialize the drawing system without fullscreen (false) and initialize the voxelmanager and its voxels.
	glS.Init(false);
	voxelmanager.Init();
}
void Game::Render()
{
	//Draw from camera.
	glS.DrawBegin();
	//Draw voxelmanager and its associated voxels.
	//voxelmanager.Render();
	//Draw a double sided reference triangle.
	glBegin(GL_TRIANGLES);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);
	glVertex3f(1,0,0);
	glVertex3f(1,0,0);
	glVertex3f(0,1,0);
	glVertex3f(0,0,0);
	glEnd();
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
	voxelmanager.Update(v);
	glS.FlyInput();
	if(glS.GetKey('R')==true)
	{
		voxelmanager.VDSphere(v,1,-0.1f,true);
	}
	//glS.Run is always called last. (timescaling/mousemovement)
	glS.Run();
}
void Game::End()
{
	//Terminate the drawing system. (closes window and terminates glfw)
	glS.Terminate();
}