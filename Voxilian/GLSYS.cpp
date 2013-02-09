#include "GLSYS.h"
GLSYS glS;
float GLSYS::Time()
{
	return ((float)clock())/CLOCKS_PER_SEC;
}
void GLSYS::Init(bool fullscreen)
{
	camera = new Camera();
	TimeScale=0.0f;
	MouseDelta.x=0;MouseDelta.y=0;MouseDelta.z=0;
	glfwInit();
	if(fullscreen==true)
	{
		glfwOpenWindow(640,480,0,0,0,0,24,0,GLFW_FULLSCREEN);
	}
	else
	{
		glfwOpenWindow(640,480,0,0,0,0,24,0,GLFW_WINDOW);
	}
	glfwSetMousePos(64,64);
	glfwSetKeyCallback(Keys);
	glfwSetMousePosCallback(MouseMove);
	glEnable(GL_DEPTH_TEST);
	glfwDisable(GLFW_MOUSE_CURSOR);
}
bool GLSYS::WindowEscaped()
{
	return ( glfwGetKey( GLFW_KEY_ESC ) == GL_FALSE && glfwGetWindowParam( GLFW_OPENED ) == GL_TRUE ) ;
}
void GLSYS::DrawBegin()
{
	glMatrixMode(GL_MODELVIEW_MATRIX);
	glClearColor(0,0.1f,0,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluPerspective(60.0f,1,0.1,100.0f);
	glRotatef(camera->pos.x,1,0,0);
	glRotatef(camera->pos.y,0,1,0);
	glRotatef(camera->pos.z,0,0,1);
	glTranslatef(camera->rot.x,camera->rot.y,camera->rot.z-5.0f);
}
void GLSYS::DrawEnd()
{
	glfwSwapBuffers();
	TimeScale=(Time()-TimeDelta);
	TimeDelta=Time();
	KeysPressed.clear();
}
void GLSYS::Terminate()
{
	glfwCloseWindow();
	glfwTerminate();
}
void Keys(int ik, int is)
{
	glS.KeysPressed.push_back(ik);
}
void MouseMove(int mx, int my)
{
	glS.MouseDelta.x=mx-64;
	glS.MouseDelta.y=my-64;
	glfwSetMousePos(64,64);
}
void GLSYS::FlyInput()
{
	float spd;
	spd=1.5f;
	if(GetKey('W'))
	{
		Math::ChF(&camera->pos.z,spd*(cos(Math::DegToRad(camera->rot.y))),TimeScale);
		Math::ChF(&camera->pos.x,spd*(-sin(Math::DegToRad(camera->rot.y))),TimeScale);
		Math::ChF(&camera->pos.y,spd*(sin(Math::DegToRad(camera->rot.x))),TimeScale);
	}
	if(GetKey('S'))
	{
		Math::ChF(&camera->pos.z,-spd*(cos(Math::DegToRad(camera->rot.y))),TimeScale);
		Math::ChF(&camera->pos.x,-spd*(-sin(Math::DegToRad(camera->rot.y))),TimeScale);
		Math::ChF(&camera->pos.y,-spd*(sin(Math::DegToRad(camera->rot.x))),TimeScale);
	}
	if(GetKey('A'))
	{
		Math::ChF(&camera->pos.z,spd*(cos(Math::DegToRad(camera->rot.y-90.0f))),TimeScale);
		Math::ChF(&camera->pos.x,spd*(-sin(Math::DegToRad(camera->rot.y-90.0f))),TimeScale);
	}
	if(GetKey('D'))
	{
		Math::ChF(&camera->pos.z,-spd*(cos(Math::DegToRad(camera->rot.y-90.0f))),TimeScale);
		Math::ChF(&camera->pos.x,-spd*(-sin(Math::DegToRad(camera->rot.y-90.0f))),TimeScale);
	}
	if(GetKey(GLFW_KEY_SPACE))
	{
		Math::ChF(&camera->pos.y,-spd,TimeScale);
	}
	if(GetKey(GLFW_KEY_LSHIFT))
	{
		Math::ChF(&camera->pos.y,spd,TimeScale);
	}
}
bool GLSYS::GetKey(int key)
{
	for(int i = 0;i<KeysPressed.size();i++)
	{
		if(KeysPressed[i]==key)
		{
			return true;
		}
	}
	return false;
}