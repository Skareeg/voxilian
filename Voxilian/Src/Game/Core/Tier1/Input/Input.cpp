#include "Input.h"

void CInput::Init()
{
	Mouse.mouseleftp=false;
	Mouse.mouseleftr=false;
	Log.Log("Input system OK.",0);
	lockmouse=true;
}

void CInput::Update(float lockX,float lockY)
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
	if(lockmouse==true)
	{
		glfwSetMousePos(lockX,lockY);
		Mouse.posX=lockX;
		Mouse.posY=lockY;
	}
	else
	{
		Mouse.posX=mx;
		Mouse.posY=my;
	}
	Mouse.mouseleftr=false;
	if(Input.GetMouse(0)==true)
	{
		Mouse.mouseleftp=true;
	}
	else
	{
		if(Mouse.mouseleftp==true)
		{
			Mouse.mouseleftr=true;
			Mouse.mouseleftp=false;
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

void CInput::Terminate()
{
}

CInput Input;