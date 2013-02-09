#ifndef GLSYS_H
#define GLSYS_H
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <GL\glfw.h>
#include "Types.h"
#include "Camera.h"
#include <ctime>
#include "Math.h"

//class for openGL SYStems
void Keys(int ik, int is);
void MouseMove(int mx, int my);
class GLSYS
{
public:
	float TimeDelta;
	std::vector<int> KeysPressed;
	Vector3 MouseDelta;
	float TimeScale;
	Camera* camera;
	void Init(bool fullscreen);
	void DrawBegin();
	void DrawEnd();
	void FlyInput();
	bool GetKey(int key);
	float Time();
	void Run();
	bool WindowEscaped();
	void Terminate();
};
extern GLSYS glS;
#endif