#ifndef H_GRAPHICS
#define H_GRAPHICS
#include <GL\glfw.h>
#include "..\Log\Log.h"
#include "..\..\Globals.h"
#include "..\Scene\Scene.h"
#include <SOIL.h>

class CCamera : public CEntity
{
public:
	float fieldOfView;
	float aspectRatio;
	float nearZ;
	float farZ;
	virtual void Init(string newname);
};

class CDraw
{
public:
	void DrawRect(float px,float py,float sx,float sy,float depth);
	void DrawRect(float px,float py,float sx,float sy,unsigned int texture,float depth);
};
class CText
{
public:
	unsigned int font;
	CText();
	void Init(string newfont);
	void DrawText(float px,float py,float depth,string text);
};

class CGraphics
{
public:
	bool cursorVisible;
	float deltaTime;
	CCamera* camera;
	bool isInit;
	bool isWindow;
	float resolution_x;
	float resolution_y;
	CDraw Draw;
	CText Text;
	CGraphics();
	void Init();
	void Window(bool fullscreen,float resx,float resy);
	unsigned int LoadTexture(std::string filename,bool minmagmaps);
	void ShowCursor(bool show);
	void Orthographic();
	void Perspective();
	void Begin();
	void End();
	void Terminate();
};

extern CGraphics Graphics;

#endif