#include "UI.h"
#include "..\..\Core.h"

Rect::Rect()
{
	px=0;
	py=0;
	sx=0;
	sy=0;
	pz=0;
}
Rect::Rect(float positionx,float positiony,float sizex,float sizey)
{
	px=positionx;
	py=positiony;
	sx=sizex;
	sy=sizey;
	pz=0;
}
Rect::Rect(float positionx,float positiony,float sizex,float sizey,float depth)
{
	px=positionx;
	py=positiony;
	sx=sizex;
	sy=sizey;
	pz=depth;
}

CDRect::CDRect()
{
	texture=0;
}

void CDRect::Draw()
{
	CUI::Window(rect,rect.pz,texture);
}

CWindow::CWindow()
{
	runfunction=nullptr;
}

bool CWindow::MousePress()
{
	if(MouseHover()==true)
	{
		if(Input.GetMouse(0)==true)
		{
			return true;
		}
	}
	return false;
}

bool CWindow::MouseHover()
{
	if(Input.Mouse.posX>rect.px&&Input.Mouse.posY>rect.py)
	{
		if(Input.Mouse.posX<rect.px+rect.sx&&Input.Mouse.posY<rect.py+rect.sy)
		{
			return true;
		}
	}
	return false;
}

void CWindow::Run()
{
	runfunction(this);
	for(int i = 0;i<windows.size();i++)
	{
		windows[i]->Run();
	}
}

void CWindow::Draw()
{
	CUI::Window(rect,rect.pz,texture);
	for(int i = 0;i<windows.size();i++)
	{
		windows[i]->Draw();
	}
}

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
		if(Input.Mouse.mouseleftr==true)
		{
			return true;
		}
	}
	return false;
}

void CButton::Draw()
{
	state=CUI::Button(rect,rect.pz,t_none,t_hover,t_press);
	if(state==CUI::NONE)
	{
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
	if(state==CUI::HOVER)
	{
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
	if(state==CUI::PRESS)
	{
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

void CCrosshair::Init(string text)
{
	if(text!="")
	{
		texture=Graphics.LoadTexture(text,false);
		rect.pz=-1;
	}
}

void CCrosshair::Draw()
{
	float mpx = Input.Mouse.posX;
	float mpy = Input.Mouse.posY;
	rect.sx=31.0f;
	rect.sy=31.0f;
	rect.px=mpx-(rect.sx/2.0f);
	rect.py=mpy-(rect.sy/2.0f);
	CDRect::Draw();
}

CUI::CUI()
{
	enabled=false;
	enabledcrosshair=false;
}

void CUI::Init(CEntity* newentity)
{
	entity=newentity;
}

CWindow* CUI::CreateWindow(Rect pos,string texture)
{
	CWindow* win = new CWindow();
	win->parentwindow=nullptr;
	win->rect=pos;
	if(texture!="")
	{
		win->texture=Graphics.LoadTexture(texture,false);
	}
	windows.push_back(win);
	return win;
}

CButton* CUI::CreateButton(Rect pos,string texturen,string textureh,string texturep)
{
	CButton* win = new CButton();
	win->parentwindow=nullptr;
	win->rect=pos;
	if(texturen!="")
	{
		win->t_none=Graphics.LoadTexture(texturen,false);
	}
	if(textureh!="")
	{
		win->t_hover=Graphics.LoadTexture(textureh,false);
	}
	if(texturep!="")
	{
		win->t_press=Graphics.LoadTexture(texturep,false);
	}
	win->texture=win->t_none;
	windows.push_back(win);
	return win;
}

void CUI::Window(Rect rect,float depth,UITex texture)
{
	Graphics.Draw.DrawRect(rect.px,rect.py,rect.sx,rect.sy,texture,depth);
}
int CUI::Button(Rect rect,float depth,UITex texturenone,UITex texturehover,UITex texturepress)
{
	if(!Input.lockmouse)
	{
		if(Input.Mouse.posX>rect.px&&Input.Mouse.posY>rect.py)
		{
			if(Input.Mouse.posX<rect.px+rect.sx&&Input.Mouse.posY<rect.py+rect.sy)
			{
				if(Input.GetMouse(0)==true)
				{
					CUI::Window(rect,depth,texturepress);
					return Btn::PRESS;
				}
				CUI::Window(rect,depth,texturehover);
				return Btn::HOVER;
			}
		}
	}
	CUI::Window(rect,depth,texturenone);
	return Btn::NONE;
}

void CUI::Update()
{
	if(enabled==true)
	{
		glPushMatrix();
		Graphics.Orthographic();
		if(!Input.lockmouse&&enabledcrosshair)
		{
			crosshair.Draw();
		}
		//UI DRAW CODES 2D
		for(int i = 0;i<windows.size();i++)
		{
			windows[i]->Draw();
		}
		Graphics.Perspective();
		glPopMatrix();
		//UI DRAW CODES 3D
		for(int i = 0;i<windows.size();i++)
		{
			windows[i]->Run();
		}
	}
}

void CUI::EnableSystem()
{
	enabled=true;
}

void CUI::EnableCrossHair(string tex)
{
	crosshair.Init(tex);
	enabledcrosshair=true;
}