#ifndef H_UI
#define H_UI
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "..\..\Tier1.h"

using namespace std;

typedef unsigned int UITex;

class Rect
{
public:
	float px;
	float py;
	float sx;
	float sy;
	float pz;
	Rect();
	Rect(float positionx,float positiony,float sizex,float sizey);
	Rect(float positionx,float positiony,float sizex,float sizey,float depth);
};

class CDRect
{
public:
	Rect rect;
	unsigned int texture;
	CDRect();
	virtual void Draw();
};

class CWindow : public CDRect
{
public:
	CWindow* parentwindow;
	vector<CWindow*> windows;
	(void)(*runfunction)(CWindow*);
	CWindow();
	bool MousePress();
	bool MouseHover();
	virtual void Run();
	virtual void Draw();
};

class CButton : public CWindow
{
public:
	UITex t_none;
	UITex t_hover;
	UITex t_press;
	int state;
	bool firenone;
	bool firehover;
	bool firepress;
	FMOD::Channel* channel;
	FMOD::Sound* sn_none;
	FMOD::Sound* sn_hover;
	FMOD::Sound* sn_press;
	CButton();
	//(void)(*buttonfunction)(CButton*);
	virtual bool Activated();
	virtual void Draw();
	void CreateSounds(string none,string hover,string press);
};

class CPanel : public CEntity , public CDRect
{
public:
	CPanel* parentpanel;
	vector<CPanel*> panels;
	/*bool MousePress();
	bool MouseHover();
	virtual void Draw();*/
};

class CCrosshair : public CDRect
{
public:
	void Init(string text);
	virtual void Draw();
};

class CUI
{
public:
	//2D window set
	vector<CWindow*> windows;
	//3D panel set
	vector<CWindow*> panels;
	CCrosshair crossHair;
	bool cursorLock;
	CUI();
	void Init();
	CWindow* CreateWindow(Rect pos,string texture);
	CButton* CreateButton(Rect pos,string texturen,string textureh,string texturep);
	enum Btn
	{
		NONE,
		HOVER,
		PRESS
	};
	void Window(Rect rect,float depth,UITex texture);
	int Button(Rect rect,float depth,UITex texturenone,UITex texturehover,UITex texturepress);
	void Update();
};

extern CUI UI;

#endif