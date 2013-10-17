#include "AdvWindow.h"

CAdvWindow::CAdvWindow()
{
	CWindow::CWindow();
	visible=true;
	borderable=true;
	closeable=false;
	modable=false;
	scrollxable=false;
	scrollyable=false;
	scrollsame=false;
	borderwidth=10.0f;
	scrollxbarwidth=10.0f;
	scrollxbarpos=0;
	scrollxbarposmin=0;
	scrollxbarposmax=0;
	scrollxmoverspeedmult=1.0f;
	scrollybarwidth=10.0f;
	scrollybarpos=0;
	scrollybarposmin=0;
	scrollybarposmax=0;
	scrollymoverspeedmult=1.0f;
	bordertexture=0;
	scrollxbartexture=0;
	scrollxmovertexture=0;
	scrollybartexture=0;
	scrollymovertexture=0;
	borderleft=nullptr;
	borderup=nullptr;
	borderright=nullptr;
	borderdown=nullptr;
	closebutton=nullptr;
	scrollxbarback=nullptr;
	scrollxbarbar=nullptr;
	scrollxbarmover=nullptr;
	scrollybarback=nullptr;
	scrollybarbar=nullptr;
	scrollybarmover=nullptr;
}
void CAdvWindow::Init(string bordertex)
{
	bordertexture=Graphics.LoadTexture(bordertex,false);
	borderleft = new CWindow();
	borderup = new CWindow();
	borderright = new CWindow();
	borderdown = new CWindow();
}
void CAdvWindow::Init(string bordertex,bool canmod)
{
	Init(bordertex);
	modable=canmod;
}
void CAdvWindow::Init(string bordertex,bool canclose,string closetex)
{
	Init(bordertex);
	closeable=canclose;
	closetexture=Graphics.LoadTexture(bordertex,false);
}
void CAdvWindow::Init(string bordertex,bool canmod,bool canclose,string closetex)
{
	Init(bordertex);
	modable=canmod;
	closeable=canclose;
	closetexture=Graphics.LoadTexture(bordertex,false);
}
void CAdvWindow::Init(string bordertex,bool canmod,bool canclose,string closetex,bool hasscrolls,string scrollbartex,string scrollmovertex)
{
	Init(bordertex,canmod,canclose,closetex);
	scrollxable=true;
	scrollyable=true;
	scrollsame=true;
	scrollxbartexture=Graphics.LoadTexture(scrollbartex,false);
	scrollxmovertexture=Graphics.LoadTexture(scrollmovertex,false);
	scrollybartexture=scrollxbartexture;
	scrollymovertexture=scrollxmovertexture;
}
void CAdvWindow::Run()
{
	if(borderleft!=nullptr&&borderup!=nullptr&&borderright!=nullptr&&borderdown!=nullptr)
	{
		borderleft->Run();
		borderup->Run();
		borderright->Run();
		borderdown->Run();
	}
	if(closeable==true)
	{
		closebutton->Run();
	}
	if(scrollxable)
	{
	}
	if(scrollyable)
	{
	}
}
void CAdvWindow::Draw()
{
}