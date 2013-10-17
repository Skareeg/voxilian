#ifndef H_INPUT
#define H_INPUT
#include <GL\glfw.h>
#include "..\Log\Log.h"

#define NKEYS 512

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
	bool startframe;
	bool terminated;
	bool lockmouse;
	int keys[NKEYS];
	void Init();
	void Update(float lockX,float lockY);
	bool GetKeyPressed(int key);
	bool GetKeyDown(int key);
	bool GetKeyReleased(int key);
	bool GetKeyAny();
	bool GetMouse(int button);
	void ResetMouse();
	void Terminate();
};

extern CInput Input;

#endif