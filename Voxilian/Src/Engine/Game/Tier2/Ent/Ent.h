#ifndef H_ENT
#define H_ENT
#include "..\..\Tier1.h"

#define ANIM_RATE 30.0f

class CEnt;

struct SANIMFRAME
{
	float p[3];
	float r[3];
};
struct SANIMSET
{
	string name;
	//Will it animate?
	bool animate;
	//Interpolation between frames.
	SANIMFRAME* transform;
	int frames;
	float frame;
	SANIMFRAME** anim;
};
//This is an attachment point.
struct SAttachmentPoint
{
	//It's name here.
	string name;
	//The current frame.
	SANIMSET* currentset;
	//The CEnt attach list.
	vector<CEnt*> attached;
	//The frame count.
	int sets;
	//The list of frames.
	SANIMSET** animset;
};

class CEnt : public CGEntity
{
public:
	btTransform transform;
	CEnt* parent;
	vector<CMesh*> meshes;
	vector<SAttachmentPoint*> attachmentpoints;
	CEnt();
	CEnt(btVector3& startposition);
	CEnt(btVector3& startposition,btQuaternion& startrotation);
	CEnt(btVector3& startposition,btVector3& startrotation);
	virtual void Init(string newname);
	virtual void Frame();
	virtual void Terminate();
	//Attach another entity to the specified attachment point.
	virtual void Attach(CEnt* attachable,string attachpoint);
	//Add in a model file, with animated frames and attachment points. (bones).
	void ProcessAttachFile(string filename);
};

#endif