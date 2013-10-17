#include "UI.h"
#include "..\..\Core0.h"

CButton::CButton()
{
	CWindow::CWindow();
	sn_none=nullptr;
	sn_hover=nullptr;
	sn_press=nullptr;
	firenone=true;
	firehover=false;
	firepress=false;
}

bool CButton::Activated()
{
	if(MouseHover()==true)
	{
		if(!Input.lockmouse)
		{
			if(Input.Mouse.mouseleftr==true)
			{
				return true;
			}
		}
	}
	return false;
}

void CButton::Draw()
{
	state=UIBtn::NONE;
	if(!Input.lockmouse)
	{
		if(Input.Mouse.posX>rect.px&&Input.Mouse.posY>rect.py)
		{
			if(Input.Mouse.posX<rect.px+rect.sx&&Input.Mouse.posY<rect.py+rect.sy)
			{
				if(Input.GetMouse(0)==true)
				{
					state=UIBtn::PRESS;
				}
				else
				{
					state=UIBtn::HOVER;
				}
			}
		}
	}
	if(state==UIBtn::NONE)
	{
		texture=t_none;
		if(!firenone)
		{
			firenone=true;
			if(sn_none!=nullptr)
			{
				Audio.PlaySound(sn_none,channel);
			}
		}
	}
	else
	{
		firenone=false;
	}
	if(state==UIBtn::HOVER)
	{
		texture=t_hover;
		if(!firehover)
		{
			firehover=true;
			if(sn_hover!=nullptr)
			{
				Audio.PlaySound(sn_hover,channel);
			}
		}
	}
	else
	{
		firehover=false;
	}
	if(state==UIBtn::PRESS)
	{
		texture=t_press;
		if(!firepress)
		{
			firepress=true;
			if(sn_press!=nullptr)
			{
				Audio.PlaySound(sn_press,channel);
			}
		}
	}
	else
	{
		firepress=false;
	}
	CWindow::Draw();
	for(int i = 0;i<windows.size();i++)
	{
		windows[i]->Draw();
	}
}

void CButton::CreateSounds(string none,string hover,string press)
{
	sn_none=Audio.CreateSound(none);
	sn_hover=Audio.CreateSound(hover);
	sn_press=Audio.CreateSound(press);
}