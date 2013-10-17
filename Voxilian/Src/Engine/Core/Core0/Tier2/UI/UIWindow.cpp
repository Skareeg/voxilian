#include "UI.h"
#include "..\..\Core0.h"

CWindow::CWindow()
{
	CDRect::CDRect();
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

void CWindow::Attach(CWindow* win)
{
	win->parentwindow=this;
	windows.push_back(win);
}

void CWindow::Run()
{
	if(runfunction!=nullptr)
	{
		runfunction(this);
	}
	for(int i = 0;i<windows.size();i++)
	{
		windows[i]->Run();
	}
}

void CWindow::Draw()
{
	//Push the matrix. Go down a tree.
	glPushMatrix();
	glTranslatef(0.0f,0.0f,rect.pz);
	//Test for parent.
	if(parentwindow!=nullptr)
	{
		//Keep drawing Rect (dpx,dpy,dpwx,dpwy) within bounds. (No drawing outside of parent Rect)
		float dpx = rect.px;
		float dpy = rect.py;
		float dpwx = rect.px+rect.sx;
		float dpwy = rect.py+rect.sy;
		Function::Clamp(&dpx,0.0f,parentwindow->rect.sx);
		Function::Clamp(&dpy,0.0f,parentwindow->rect.py);
		Function::Clamp(&dpwx,0.0f,parentwindow->rect.sx);
		Function::Clamp(&dpwy,0.0f,parentwindow->rect.py);
		//Test in-bound points.
		if(dpwx!=0&&dpwy!=0&&dpx<parentwindow->rect.sx&&dpy<parentwindow->rect.sy)
		{
			if(dpx!=dpwx&&dpy!=dpwy)
			{
				//Create the widths.
				float wx = dpwx-dpx;
				float wy = dpwy-dpy;
				glTranslatef(dpx,dpy,0.0f);
				CUI::Window(Rect(0,0,wx,wy),Rect(0,0,1,1),0,texture);
				for(int i = 0;i<windows.size();i++)
				{
					windows[i]->Draw();
				}
			}
		}
	}
	else
	{
		//Perform no-test drawing.
		glTranslatef(rect.px,rect.py,0.0f);
		CUI::Window(Rect(0,0,rect.sx,rect.sy),Rect(trect.px,trect.py,trect.sx,trect.sy),0,texture);
		for(int i = 0;i<windows.size();i++)
		{
			windows[i]->Draw();
		}
	}
	glPopMatrix();
}