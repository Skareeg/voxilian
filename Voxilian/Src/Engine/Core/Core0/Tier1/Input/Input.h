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
	void SetPos(int mx, int my);
};

class CInput
{
public:
	CMouse Mouse;
	bool startframe;
	bool terminated;
	bool lockmouse;
	int keys[NKEYS];
	CInput();
	void Init(float lockX,float lockY);
	void Update();
	void MouseGet();
	bool GetKeyPressed(int key);
	bool GetKeyDown(int key);
	bool GetKeyReleased(int key);
	bool GetKeyAny();
	bool GetMouse(int button);
	void ResetMouse();
	void Terminate();
	void LockMouse(bool lock);
};

//InputStruct, requiring type, i, j, the object to call to.
struct InputStruct
{
	int type;
	int i;
	int j;
	void* object;
};
//The typedef for Input Callback (returns void, requires InputStruct.
typedef void (*InputCallback)(InputStruct);
//Struct requiring the call to be made and the object to associate with it.
struct InputCallObjPair
{
	InputCallback call;
	void* object;
};
namespace InputEnum
{
	enum inputENUM
	{
		KEY,
		CHAR,
		MB,
		MP,
		MW
	};
};
extern vector<InputCallObjPair> InputFuncs;
void inputkeysfunc(int i,int j);
void inputcharsfunc(int i,int j);
void inputmousebuttonsfunc(int i,int j);
void inputmouseposfunc(int i,int j);
void inputmousewheelfunc(int i);

extern CInput Input;

#endif