#include "FlyCam.h"

CGFlyCam::CGFlyCam()
{
	CEntity::CEntity();
	camera=nullptr;
}
void CGFlyCam::Init(string newname)
{
	CEntity::Init(newname);
	SetType("CGFlyCam");
	camera = new CCamera();
	speed_aim=10.0f;
	speed_move=10.0f;
	mult_sprint=2.5f;
	aimxmax=87;
}
void CGFlyCam::Frame()
{
	CEntity::Frame();
	if(camera)
	{
		camera->euler+=btVector3(-Input.Mouse.deltaY*Graphics.deltaTime*speed_aim,-Input.Mouse.deltaX*Graphics.deltaTime*speed_aim,0.0f);
		float tx = camera->euler.x();
		if(tx<-aimxmax)
		{
			tx=-aimxmax;
		}
		if(tx>aimxmax)
		{
			tx=aimxmax;
		}
		camera->euler.setX(tx);
		float x = camera->euler.x() * (PI/180.0f);
		float y = camera->euler.y() * (PI/180.0f);
		float spd = speed_move;
		if(Input.GetKeyDown(GLFW_KEY_LSHIFT))
		{
			spd*=mult_sprint;
		}
		if(Input.GetKeyDown('W'))
		{
			camera->position+=btVector3(-sinf(y),sinf(x),cosf(y))*spd*Graphics.deltaTime;
		}
		if(Input.GetKeyDown('S'))
		{
			camera->position-=btVector3(-sinf(y),sinf(x),cosf(y))*spd*Graphics.deltaTime;
		}
		if(Input.GetKeyDown('A'))
		{
			camera->position+=btVector3(-sinf((y-(PI/2.0f))),0.0f,cosf((y-(PI/2.0f))))*spd*Graphics.deltaTime;
		}
		if(Input.GetKeyDown('D'))
		{
			camera->position+=btVector3(-sinf((y+(PI/2.0f))),0.0f,cosf((y+(PI/2.0f))))*spd*Graphics.deltaTime;
		}
	}
}