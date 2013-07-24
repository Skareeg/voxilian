#include "Input.h"

void CInput::Init()
{
	Mouse.mouseleftp=false;
	Mouse.mouseleftr=false;
	Log.Log("Input system OK.",0);
}

void CInput::Update(bool cursorLock,float lockX,float lockY)
{
	int mx = 0;
	int my = 0;
	glfwGetMousePos(&mx,&my);
	Mouse.deltaX=Mouse.posX-mx;
	Mouse.deltaY=Mouse.posY-my;
	if(cursorLock==true)
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

bool CInput::GetKey(int key)
{
	glfwPollEvents();
	if(glfwGetKey(key)==GLFW_PRESS)
	{
		return true;
	}
	if(glfwGetKey(key)==GLFW_RELEASE)
	{
		return false;
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