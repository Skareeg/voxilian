#ifndef VOX_H
#define VOX_H
#include "..\..\Utilities\Types.h"
#include <vector>
#include <string>
#include "..\..\Utilities\simplexnoise.h"
#include <ctime>
#include "..\..\Utilities\GLSYS.h"
#include <fstream>
#include <stdio.h>

#define V_C_SIZEX 5
#define V_C_SIZEY 5
#define V_C_SIZEZ 5
#define V_C_SCALEX 1.0f/((float)V_C_SIZEX)
#define V_C_SCALEY 1.0f/((float)V_C_SIZEY)
#define V_C_SCALEZ 1.0f/((float)V_C_SIZEZ)

#define V_TYPE_MESH 0
#define V_TYPE_CUBE 1

#define VNULL chunk->dimensia->manager->voxnull
#define CNULL dimensia->manager->vcnull

struct VAV
{
	GLfloat x,y,z;
	GLfloat r,g,b;
};

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
struct VDensity
{
	int vox_type;
	float vox_density;
	int vox_id;
	VoxelCell vcell;
	vector<Triangle> vmesh;
	string name;
};
struct VDestructor
{
	Vector3 pos;
	float radius;
	float impactsoft;
	float impactsolid;
};

#define VVALID 99999

class VVoxel
{
public:
	string name;
	VChunk* chunk;
	VIndex position;
	VIndex index;
	vector<VDensity> densities;
	VVoxel* ne[3][3][3];
	int drawsides[6];
	int state;
	vector<Triangle> vmesh;
	VoxelCell vcell;
	VVoxel();
	void Init(VChunk* c,VIndex p);
	void Render();
	void Save(fstream* f);
	void Load(fstream* f);
	void VCalculate();
	void NCalculate();
	bool isInit;
	bool isNC;
	bool isVC;
	GLFWmutex vm;
	bool VCALCing;
	int valid;
};

class VChunk
{
public:
	vector<Vector3> b_lines;
	vector<Vector3> d_lines;
	int state;
	VDimensia* dimensia;
	VIndex position;
	fstream regionfile;
	GLFWthread updatethread;
	VVoxel voxels[V_C_SIZEX][V_C_SIZEY][V_C_SIZEZ];
	VChunk* ne[3][3][3];
	vector<Triangle> cmesh;
	bool render;
	GLFWmutex nodestroy;
	VChunk(VDimensia* d,VIndex nposition);
	void Init();
	void Update();
	void Render();
	void Destroy();
	VIndex GetPos();
	int GetX();
	int GetY();
	int GetZ();
	void NCalculate();
	void VCalculate();
	bool isInit;
	bool isNC;
	bool isVC;
};

//Voxel Dimension class.
class VDimensia
{
public:
	//The voxels current state. > 0==initialize : 1==update : 2==neighbor : 3==vcalc <
	int state;
	//The dimensional name.
	string name;
	//The voxel dimensions current manager.
	VManager* manager;
	//The voxel chunks.
	vector<VChunk*> chunks;
	//This is the chunk creation-by-search thread.
	GLFWthread thread_chunk_manage;
	//This is the chunk destruction thread.
	GLFWthread thread_chunk_destroy;
	//This is the voxel update thread.
	GLFWthread thread_voxel_update;
	//This is the voxel isolevel.
	float isolevel;
	//The dimensions contructor.
	VDimensia(VManager* m,string nm);
	//The render method.
	void Render();
	//This will get a chunk from a position or return nullptr
	VChunk* GetChunk(VDimensia* dimensia,VIndex pos);
	//This will get a voxel from a world position or return nullptr
	VVoxel* GetVoxel(VIndex wpos);
	//
	//These are the voxel changing functions. They will occur in realtime.
	//
	void VoxelDestroySphere(Vector3 pos,float size,float soft,float hard);
	vector<VDestructor> vox_destruct;
};

//Voxel Manager class.
class VManager
{
public:
	//This is the null Voxel.
	VVoxel* voxnull;
	VChunk* vcnull;
	//The openGL Camera position.
	Vector3* camera_pos;
	//The voxel dimension.
	VDimensia* dimensia;
	//This the chunk creation radius.
	float distance_create;
	//This is the max chunk render distance.
	float distance_render;
	//This is the max chunk update distance.
	float distance_update;
	//Voxel Manager initialization method. (Requires openGL Camera position.)
	void Init(Vector3* campos);
	//Voxel Manager render method.
	void Render();
};

#endif