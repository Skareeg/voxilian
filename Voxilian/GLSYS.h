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

#define VEC_FWD VMath::Vector(0,0,1)
#define VEC_BWD VMath::Vector(0,0,-1)
#define VEC_LFT VMath::Vector(-1,0,0)
#define VEC_RGT VMath::Vector(1,0,0)
#define VEC_DN VMath::Vector(0,-1,0)
#define VEC_UP VMath::Vector(0,1,0)

#define DRAW_FWD VMath::Vector(0,0,-1)
#define DRAW_BWD VMath::Vector(0,0,1)
#define DRAW_LFT VMath::Vector(-1,0,0)
#define DRAW_RGT VMath::Vector(1,0,0)
#define DRAW_DN VMath::Vector(0,-1,0)
#define DRAW_UP VMath::Vector(0,1,0)

#define LOG(st) glS.log.Log(st)

//class for openGL SYStems
void MouseMove();
void gTrans(float x,float y,float z);
class GLSYS
{
public:
	LogFile log;
	float TimeDelta;
	std::vector<int> KeysPressed;
	Vector3 MouseDelta;
	float TimeScale;
	Camera* camera;
	void Init(bool fullscreen);
	void Run();
	void DrawBegin();
	void DrawEnd();
	void FlyInput();
	bool GetKey(int key);
	float Time();
	bool WindowEscaped();
	void Terminate();
};
extern GLSYS glS;
#define DRAW_CUBE_DOWN 0
#define DRAW_CUBE_UP 5
#define DRAW_CUBE_LEFT 1
#define DRAW_CUBE_RIGHT 2
#define DRAW_CUBE_FORWARD 4
#define DRAW_CUBE_BACKWARD 3
namespace Draw
{
	void Cube(float i,float j,float k);
	void CubeSide(float i,float j,float k,int* l);
};
#endif