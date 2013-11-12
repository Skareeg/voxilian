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
	float lockX;
	float lockY;
	bool mouseleftp;
	bool mouselefth;
	bool mouseleftr;
	bool mouserightp;
	bool mouserighth;
	bool mouserightr;
};

class CInput
{
public:
	CMouse Mouse;
	bool startframe;
	bool terminated;
	bool lockmouse;
	int keys[NKEYS];
	void Init(float lockX,float lockY);
	void Update();
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