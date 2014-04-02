#ifndef H_MEntity
#define H_MEntity
#include "..\..\Tier1\Tier1.h"
#include "..\..\Tier2\Tier2.h"

class CMEntity : public CEntity
{
public:
	btTransform transform;
	CMesh mesh;
	CMEntity();
	CMEntity(btVector3& startposition);
	virtual void Init(string newname);
	virtual void Update();
	virtual void Render();
	bool AddMesh(string filename);
};

#endif