#ifndef H_INPUT
#define H_INPUT
#include <GL\glfw.h>
#include "..\Log\Log.h"

class CMouse
{
public:
	float posX;
	float posY;
	float deltaX;
	float deltaY;
	bool mouseleftp;
	bool mouseleftr;
};

class CInput
{
public:
	CMouse Mouse;
	void Init();
	void Update(bool cursorLock,float lockX,float lockY);
	bool GetKey(int key);
	bool GetMouse(int button);
	void Terminate();
};

extern CInput Input;

#endif