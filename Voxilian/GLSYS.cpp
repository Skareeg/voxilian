#include "GLSYS.h"
//Create the external GLSYS drawing system as glS.
GLSYS glS;
float GLSYS::Time()
{
	return ((float)clock())/CLOCKS_PER_SEC;
}
void GLSYS::Init(bool fullscreen)
{
	camera = new Camera();
	camera->pos.z=-5;
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
	glEnable(GL_DEPTH_TEST);
	glfwDisable(GLFW_MOUSE_CURSOR);
	glfwSwapInterval(1);
}
bool GLSYS::WindowEscaped()
{
	return ( glfwGetKey( GLFW_KEY_ESC ) == GL_TRUE || glfwGetWindowParam( GLFW_OPENED ) == GL_FALSE ) ;
}
void GLSYS::DrawBegin()
{
	glMatrixMode(GL_MODELVIEW_MATRIX);
	glClearColor(0,0.0f,0,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluPerspective(60.0f,1,0.1,100.0f);
	glRotatef(180.0f,0,1,0);
	glRotatef(camera->rot.x,1,0,0);
	glRotatef(camera->rot.y,0,1,0);
	glRotatef(camera->rot.z,0,0,1);
	gTrans(-camera->pos.x,-camera->pos.y,-camera->pos.z);
}
void GLSYS::DrawEnd()
{
	glfwSwapBuffers();
}
void GLSYS::Terminate()
{
	glfwCloseWindow();
	glfwTerminate();
}
void MouseMove()
{
	int mx = 0;
	int my = 0;
	glfwPollEvents();
	glfwGetMousePos(&mx,&my);
	glS.MouseDelta.x=mx-64;
	glS.MouseDelta.y=my-64;
	glfwSetMousePos(64,64);
}
void GLSYS::FlyInput()
{
	float spd;
	spd=1.5f;
	camera->rot.y+=MouseDelta.x*0.1f;
	camera->rot.x-=MouseDelta.y*0.1f;
	if(GetKey('W')==true)
	{
		Math::ChF(&camera->pos.z,spd*(cos(Math::DegToRad(camera->rot.y))*cos(Math::DegToRad(camera->rot.x))),TimeScale);
		Math::ChF(&camera->pos.x,spd*(-sin(Math::DegToRad(camera->rot.y))*cos(Math::DegToRad(camera->rot.x))),TimeScale);
		Math::ChF(&camera->pos.y,spd*(sin(Math::DegToRad(camera->rot.x))),TimeScale);

	}
	if(GetKey('S')==true)
	{
		Math::ChF(&camera->pos.z,-spd*(cos(Math::DegToRad(camera->rot.y))*cos(Math::DegToRad(camera->rot.x))),TimeScale);
		Math::ChF(&camera->pos.x,-spd*(-sin(Math::DegToRad(camera->rot.y))*cos(Math::DegToRad(camera->rot.x))),TimeScale);
		Math::ChF(&camera->pos.y,-spd*(sin(Math::DegToRad(camera->rot.x))),TimeScale);
	}
	if(GetKey('A')==true)
	{
		Math::ChF(&camera->pos.z,spd*(cos(Math::DegToRad(camera->rot.y-90.0f))),TimeScale);
		Math::ChF(&camera->pos.x,spd*(-sin(Math::DegToRad(camera->rot.y-90.0f))),TimeScale);
	}
	if(GetKey('D')==true)
	{
		Math::ChF(&camera->pos.z,-spd*(cos(Math::DegToRad(camera->rot.y-90.0f))),TimeScale);
		Math::ChF(&camera->pos.x,-spd*(-sin(Math::DegToRad(camera->rot.y-90.0f))),TimeScale);
	}
	if(GetKey(GLFW_KEY_SPACE)==true)
	{
		Math::ChF(&camera->pos.y,spd,TimeScale);
	}
	if(GetKey(GLFW_KEY_LSHIFT)==true)
	{
		Math::ChF(&camera->pos.y,-spd,TimeScale);
	}
}
bool GLSYS::GetKey(int key)
{
	glfwPollEvents();
	if(glfwGetKey(key)==GLFW_PRESS)
	{
		return true;
	}
	return false;
}
void GLSYS::Run()
{
	TimeScale=(Time()-TimeDelta);
	TimeDelta=Time();
	MouseMove();
}
void gTrans(float x,float y,float z)
{
	glTranslatef(x,y,z);
}
void Draw::Cube(float i,float j,float k)
{
	glColor3f(1,0,0);
	glVertex3f(i,j,-k);
	glVertex3f(i+1,j,-k);
	glVertex3f(i+1,j,-k-1);
	glVertex3f(i+1,j,-k-1);
	glVertex3f(i,j,-k-1);
	glVertex3f(i,j,-k);

	glColor3f(1,1,0);
	glVertex3f(i,j+1,-k);
	glVertex3f(i+1,j+1,-k);
	glVertex3f(i+1,j+1,-k-1);
	glVertex3f(i+1,j+1,-k-1);
	glVertex3f(i,j+1,-k-1);
	glVertex3f(i,j+1,-k);

	glColor3f(0,1,0);
	glVertex3f(i,j,-k);
	glVertex3f(i,j+1,-k);
	glVertex3f(i,j+1,-k-1);
	glVertex3f(i,j+1,-k-1);
	glVertex3f(i,j,-k-1);
	glVertex3f(i,j,-k);

	glColor3f(0,1,1);
	glVertex3f(i+1,j,-k);
	glVertex3f(i+1,j+1,-k);
	glVertex3f(i+1,j+1,-k-1);
	glVertex3f(i+1,j+1,-k-1);
	glVertex3f(i+1,j,-k-1);
	glVertex3f(i+1,j,-k);

	glColor3f(0,0,1);
	glVertex3f(i,j,-k);
	glVertex3f(i,j+1,-k);
	glVertex3f(i+1,j+1,-k);
	glVertex3f(i+1,j+1,-k);
	glVertex3f(i+1,j,-k);
	glVertex3f(i,j,-k);

	glColor3f(1,0,1);
	glVertex3f(i,j,-k-1);
	glVertex3f(i,j+1,-k-1);
	glVertex3f(i+1,j+1,-k-1);
	glVertex3f(i+1,j+1,-k-1);
	glVertex3f(i+1,j,-k-1);
	glVertex3f(i,j,-k-1);
}
void Draw::CubeSide(float i,float j,float k,int* l)
{
	if(l[DRAW_CUBE_DOWN]==1)
	{
		glColor3f(1,0,0);
		glVertex3f(i,j,-k);
		glVertex3f(i+1,j,-k);
		glVertex3f(i+1,j,-k-1);
		glVertex3f(i+1,j,-k-1);
		glVertex3f(i,j,-k-1);
		glVertex3f(i,j,-k);
	}
	if(l[DRAW_CUBE_UP]==1)
	{
		glColor3f(1,1,0);
		glVertex3f(i,j+1,-k);
		glVertex3f(i+1,j+1,-k);
		glVertex3f(i+1,j+1,-k-1);
		glVertex3f(i+1,j+1,-k-1);
		glVertex3f(i,j+1,-k-1);
		glVertex3f(i,j+1,-k);
	}
	if(l[DRAW_CUBE_LEFT]==1)
	{
		glColor3f(0,1,0);
		glVertex3f(i,j,-k);
		glVertex3f(i,j+1,-k);
		glVertex3f(i,j+1,-k-1);
		glVertex3f(i,j+1,-k-1);
		glVertex3f(i,j,-k-1);
		glVertex3f(i,j,-k);
	}
	if(l[DRAW_CUBE_RIGHT]==1)
	{
		glColor3f(0,1,1);
		glVertex3f(i+1,j,-k);
		glVertex3f(i+1,j+1,-k);
		glVertex3f(i+1,j+1,-k-1);
		glVertex3f(i+1,j+1,-k-1);
		glVertex3f(i+1,j,-k-1);
		glVertex3f(i+1,j,-k);
	}
	if(l[DRAW_CUBE_BACKWARD]==1)
	{
		glColor3f(0,0,1);
		glVertex3f(i,j,-k);
		glVertex3f(i,j+1,-k);
		glVertex3f(i+1,j+1,-k);
		glVertex3f(i+1,j+1,-k);
		glVertex3f(i+1,j,-k);
		glVertex3f(i,j,-k);
	}
	if(l[DRAW_CUBE_FORWARD]==1)
	{
		glColor3f(1,0,1);
		glVertex3f(i,j,-k-1);
		glVertex3f(i,j+1,-k-1);
		glVertex3f(i+1,j+1,-k-1);
		glVertex3f(i+1,j+1,-k-1);
		glVertex3f(i+1,j,-k-1);
		glVertex3f(i,j,-k-1);
	}
}