#include "UI.h"
#include "..\..\Core0.h"

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
	rect=Rect(0,0,0,0);
	trect=Rect(0,0,1,1);
}

void CDRect::Draw()
{
	CUI::Window(rect,trect,rect.pz,texture);
}

CCrosshair::CCrosshair()
{
	CDRect::CDRect();
	enabled=false;
	trect=Rect(0,0,1,1);
}
void CCrosshair::Init(string text)
{
	if(!enabled)
	{
		enabled=true;
		if(text!="")
		{
			texture=Graphics.LoadTexture(text,false);
			rect.pz=-1;
			ptext=text;
		}
		else
		{
			ptext="";
		}
		enabledcrosshair=false;
	}
	else
	{
		if(ptext!=text&&ptext!=""&&texture>0)
		{
			Graphics.FreeTexture(texture);
			texture=Graphics.LoadTexture(text,false);
			ptext=text;
		}
	}
}

void CCrosshair::Update()
{
	glPushMatrix();
	Graphics.Orthographic();
	if(!Input.lockmouse&&enabledcrosshair)
	{
		int mpx = 0;
		int mpy = 0;
		glfwGetMousePos(&mpx,&mpy);
		rect.sx=31.0f;
		rect.sy=31.0f;
		rect.px=mpx-(rect.sx/2.0f);
		rect.py=mpy-(rect.sy/2.0f);
		Draw();
	}
	glPopMatrix();
}
CCrosshair Crosshair;

CUI::CUI()
{
	enabled=false;
}

void CUI::Init(CEntity* newentity)
{
	entity=newentity;
}

CWindow* CUI::UICreateWindow(Rect pos,string texture)
{
	CWindow* win = new CWindow();
	win->parentwindow=nullptr;
	win->rect=pos;
	win->trect=Rect(0,0,1,1);
	if(texture!="")
	{
		win->texture=Graphics.LoadTexture(texture,false);
	}
	windows.push_back(win);
	return win;
}

CButton* CUI::UICreateButton(Rect pos,string texturen,string textureh,string texturep)
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

void CUI::Window(Rect rect,Rect trect,float depth,UITex texture)
{
	Graphics.Draw.DrawRect(rect.px,rect.py,rect.sx,rect.sy,
		trect.px,trect.py,trect.sx,trect.sy,
		texture,depth);
}
int CUI::Button(Rect rect,Rect trect,float depth,UITex texturenone,UITex texturehover,UITex texturepress)
{
	if(!Input.lockmouse)
	{
		if(Input.Mouse.posX>rect.px&&Input.Mouse.posY>rect.py)
		{
			if(Input.Mouse.posX<rect.px+rect.sx&&Input.Mouse.posY<rect.py+rect.sy)
			{
				if(Input.GetMouse(0)==true)
				{
					CUI::Window(rect,trect,depth,texturepress);
					return UIBtn::PRESS;
				}
				CUI::Window(rect,trect,depth,texturehover);
				return UIBtn::HOVER;
			}
		}
	}
	CUI::Window(rect,trect,depth,texturenone);
	return UIBtn::NONE;
}

void CUI::Update()
{
	if(enabled==true)
	{
		glPushMatrix();
		Graphics.Orthographic();
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
	Crosshair.Init(tex);
	Crosshair.enabledcrosshair=true;
}