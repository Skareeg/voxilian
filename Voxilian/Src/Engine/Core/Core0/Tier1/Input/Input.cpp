#include "Input.h"

void CMouse::SetPos(int mx, int my)
{
	glfwSetMousePos(mx,my);
	deltaX=mx-posX;
	deltaY=my-posY;
	posX=mx;
	posY=my;
}

CInput::CInput()
{
}

void CInput::Init(float lockX,float lockY)
{
	terminated=false;
	Mouse.mouseleftp=false;
	Mouse.mouseleftr=false;
	Log.Log("Input system OK.",0);
	lockmouse=true;
	startframe=true;
	Mouse.lockX=lockX;
	Mouse.lockY=lockY;
	glfwSetKeyCallback(inputkeysfunc);
	glfwSetCharCallback(inputcharsfunc);
	glfwSetMouseButtonCallback(inputmousebuttonsfunc);
	glfwSetMousePosCallback(inputmouseposfunc);
	glfwSetMouseWheelCallback(inputmousewheelfunc);
}

void CInput::Update()
{
	glfwPollEvents();
	for(int i = 0;i<NKEYS;i++)
	{
		int press = glfwGetKey(i);
		if(press==GLFW_PRESS)
		{
			if(keys[i]==1)
			{
				keys[i]=2;
			}
			if(keys[i]==0)
			{
				keys[i]=1;
			}
		}
		else
		{
			if(keys[i]==3)
			{
				keys[i]=0;
			}
			if(keys[i]==2)
			{
				keys[i]=3;
			}
		}
	}
	MouseGet();
	Mouse.mouseleftp=false;
	Mouse.mouseleftr=false;
	if(Input.GetMouse(0)==true&&!Mouse.mouselefth)
	{
		Mouse.mouseleftp=true;
	}
	if(Input.GetMouse(0)==true)
	{
		Mouse.mouselefth=true;
	}
	else
	{
		if(Mouse.mouselefth==true)
		{
			Mouse.mouseleftr=true;
			Mouse.mouselefth=false;
		}
	}
	Mouse.mouserightp=false;
	Mouse.mouserightr=false;
	if(Input.GetMouse(2)==true&&!Mouse.mouserighth)
	{
		Mouse.mouserightp=true;
	}
	if(Input.GetMouse(2)==true)
	{
		Mouse.mouserighth=true;
	}
	else
	{
		if(Mouse.mouserighth==true)
		{
			Mouse.mouserightr=true;
			Mouse.mouserighth=false;
		}
	}
}
void CInput::MouseGet()
{
	int mx = 0;
	int my = 0;
	glfwGetMousePos(&mx,&my);
	Mouse.deltaX=Mouse.posX-mx;
	Mouse.deltaY=Mouse.posY-my;
	if(startframe==true)
	{
		ResetMouse();
		startframe=false;
	}
	if(lockmouse==true)
	{
		glfwSetMousePos(Mouse.lockX,Mouse.lockY);
		Mouse.posX=Mouse.lockX;
		Mouse.posY=Mouse.lockY;
	}
	else
	{
		Mouse.posX=mx;
		Mouse.posY=my;
	}
}
bool CInput::GetKeyPressed(int key)
{
	if(keys[key]==1)
	{
		return true;
	}
	return false;
}
bool CInput::GetKeyDown(int key)
{
	if(keys[key]==1||keys[key]==2)
	{
		return true;
	}
	return false;
}
bool CInput::GetKeyReleased(int key)
{
	if(keys[key]==3)
	{
		return true;
	}
	return false;
}
bool CInput::GetKeyAny()
{
	for(int i = 0;i<NKEYS;i++)
	{
		if(keys[i]>0)
		{
			return true;
		}
	}
	return false;
}

bool CInput::GetMouse(int button)
{
	if(button==0)
	{
		if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
		{
			return true;
		}
		return false;
	}
	if(button==1)
	{
		if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_MIDDLE)==GLFW_PRESS)
		{
			return true;
		}
		return false;
	}
	if(button==2)
	{
		if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS)
		{
			return true;
		}
		return false;
	}
	return false;
}

void CInput::ResetMouse()
{
	Mouse.deltaX=0;
	Mouse.deltaY=0;
	Mouse.mouseleftp=false;
	Mouse.mouselefth=false;
	Mouse.mouseleftr=false;
	Mouse.mouserightp=false;
	Mouse.mouserighth=false;
	Mouse.mouserightr=false;
}

void CInput::Terminate()
{
	if(!terminated)
	{
		Log.Log("Input Terminated Successfully.",0);
		terminated=true;
	}
}

void CInput::LockMouse(bool lock)
{
	lockmouse=lock;
}

vector<InputCallObjPair> InputFuncs;

void inputkeysfunc(int i,int j)
{
	InputStruct out;
	out.i=i;
	out.j=j;
	out.type=InputEnum::KEY;
	for(int k = 0;k<InputFuncs.size();k++)
	{
		out.object=InputFuncs[k].object;
		InputFuncs[k].call(out);
	}
}
void inputcharsfunc(int i,int j)
{
	InputStruct out;
	out.i=i;
	out.j=j;
	out.type=InputEnum::CHAR;
	for(int k = 0;k<InputFuncs.size();k++)
	{
		out.object=InputFuncs[k].object;
		InputFuncs[k].call(out);
	}
}
void inputmousebuttonsfunc(int i,int j)
{
	InputStruct out;
	out.i=i;
	out.j=j;
	out.type=InputEnum::MB;
	for(int k = 0;k<InputFuncs.size();k++)
	{
		out.object=InputFuncs[k].object;
		InputFuncs[k].call(out);
	}
}
void inputmouseposfunc(int i,int j)
{
	Input.MouseGet();
	InputStruct out;
	out.i=i;
	out.j=j;
	out.type=InputEnum::MP;
	for(int k = 0;k<InputFuncs.size();k++)
	{
		out.object=InputFuncs[k].object;
		InputFuncs[k].call(out);
	}
}
void inputmousewheelfunc(int i)
{
	InputStruct out;
	out.i=i;
	out.type=InputEnum::MW;
	for(int k = 0;k<InputFuncs.size();k++)
	{
		out.object=InputFuncs[k].object;
		InputFuncs[k].call(out);
	}
	//Set it back to zero, because, for god knows why, "i" IS THE FREAKING POSITION VALUE!
	glfwSetMouseWheel(0);
}

CInput Input;