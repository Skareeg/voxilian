#ifndef H_GFLYCAM
#define H_GFLYCAM
#include "..\..\..\Core\Core.h"

class CGFlyCam : public CEntity
{
public:
	CCamera* camera;
	float aimxmax;
	float speed_aim;
	float speed_move;
	float mult_sprint;
	CGFlyCam();
	virtual void Init(string newname);
	virtual void Frame();
};

#endif