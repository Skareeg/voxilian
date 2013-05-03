#ifndef VOX_H
#define VOX_H
#include "..\..\Utilities\Types.h"
#include <vector>
#include <string>
#include "..\..\Utilities\simplexnoise.h"
#include <ctime>
#include "..\..\Utilities\GLSYS.h"

#define V_C_SIZEX 16
#define V_C_SIZEY 16
#define V_C_SIZEZ 16

#define V_TYPE_CUBE 0
#define V_TYPE_MESH 0

#define VCH vector<VChunk*>

class VIndex
{
public:
	int x;
	int y;
	int z;
	void FromVector3(Vector3 v);
	Vector3 ToVector3();
	bool Compare(VIndex v);
	VIndex operator+(VIndex v);
	VIndex operator-(VIndex v);
};

static VIndex VINDEX(int i,int j,int k);

class VManager;
class VDimensia;
class VChunk;
class VVoxel;

class VVoxel
{
public:
	VIndex position;
	VChunk* chunk;
	VVoxel* neighbors[3][3][3];
	int type;
	float density;
	float temperature;
	vector<Triangle> mesh;
	void Init(VChunk* ch,VIndex pos);
	void Update();
	void Calculate();
	void Render();
	void Neighbors();
};

class VChunk
{
public:
	bool delflag;
	VIndex position;
	VDimensia* dimensia;
	VVoxel voxels[V_C_SIZEX][V_C_SIZEY][V_C_SIZEZ];
	vector<VVoxel*> vpointers;
	VChunk* neighbors[3][3][3];
	void Init(VDimensia* dm,VIndex indpos);
	void Update();
	void Calculate();
	void Render();
	void Neighbors();
	void VNeighbors();
};

class VCInd
{
public:
	int number;
	int size;
};

class VDimensia
{
public:
	GLFWthread createthread;
	GLFWthread destroythread;
	GLFWmutex dmutex;
	int state;
	string name;
	Vector3 rndvec;
	VIndex position;
	VManager* manager;
	int mindist;
	int maxdist;
	VCH chunks_c;
	VCH chunks_r;
	vector<int> chunks_d;
	vector<VIndex> index;
	void Update();
	VDimensia(VManager* m,string nname);
	VChunk* GetChunk(VIndex vind);
};

class VManager
{
public:
	Vector3* cameraposition;
	vector<VDimensia*> dimensias;
	VDimensia* dimensia;
	void Init(Camera* c);
	void Update();
};

#endif