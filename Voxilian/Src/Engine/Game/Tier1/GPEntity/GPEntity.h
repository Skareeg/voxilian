#ifndef H_GPENTITY
#define H_GPENTITY
#include "..\..\..\Core\Core.h"

class CGPEntity : public CPEntity
{
public:
	CGPEntity();
	CGPEntity(btVector3& startposition);
	virtual void Init(string newname);
	virtual void Frame();
	virtual void Terminate();
};

#endif