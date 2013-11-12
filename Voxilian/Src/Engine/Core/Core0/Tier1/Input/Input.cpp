#include "Input.h"

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
	if(keys[key]>0)
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

CInput Input;