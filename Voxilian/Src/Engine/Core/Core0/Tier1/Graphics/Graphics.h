#ifndef H_GRAPHICS
#define H_GRAPHICS
#include <GL\glfw.h>
#include "..\Log\Log.h"
#include "..\..\Globals.h"
#include "..\Entity\Entity.h"
#include <SOIL.h>

float cF(float f,float a);

class CCamera : public CEntity
{
public:
	float fieldOfView;
	float aspectRatio;
	float nearZ;
	float farZ;
	btVector3 position;
	btVector3 euler;
	btQuaternion rotation;
	bool useQuat;
	CCamera();
	virtual void Init(string newname);
};

class CDrawPure
{
public:
	void DrawQuad(btVector3* points,btVector3& color);
};
class CDraw
{
public:
	CDrawPure pure;
	void DrawRect(float px,float py,float sx,float sy,float depth);
	void DrawRect(float px,float py,float sx,float sy,unsigned int texture,float depth);
	void DrawRect(float px,float py,float sx,float sy,float tpx,float tpy,float tsx,float tsy,unsigned int texture,float depth);
	void DrawQuad(btVector3* points,btVector3& color);
	void DrawCube(btVector3& pos,float size);
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
	bool terminated;
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
	unsigned int LoadTexture(std::string filename,bool minmagmaps,bool autotex);
	void FreeTexture(unsigned int texture);
	void ShowCursor(bool show);
	void Orthographic();
	void Perspective();
	void Begin();
	void End();
	void SetCamera(CCamera* newcam);
	void Terminate();
};

extern CGraphics Graphics;

#endif