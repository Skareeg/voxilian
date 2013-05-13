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

#define V_C_SIZEX 20
#define V_C_SIZEY 20
#define V_C_SIZEZ 20
#define V_C_SCALEX 1.0f/((float)V_C_SIZEX)
#define V_C_SCALEY 1.0f/((float)V_C_SIZEY)
#define V_C_SCALEZ 1.0f/((float)V_C_SIZEZ)

#define V_TYPE_MESH 0
#define V_TYPE_CUBE 1

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
	string name;
};

class VVoxel
{
public:
	VChunk* chunk;
	VIndex position;
	vector<VDensity> densities;
	VVoxel* ne[3][3][3];
	void Init(VChunk* c,VIndex p);
	void Render();
	void Save(fstream* f);
	void Load(fstream* f);
	void Calculate();
};

class VChunk
{
public:
	int state;
	VDimensia* dimensia;
	VIndex position;
	fstream regionfile;
	GLFWthread updatethread;
	VVoxel voxels[V_C_SIZEX][V_C_SIZEY][V_C_SIZEZ];
	VChunk* ne[3][3][3];
	VoxelCell vcell;
	VChunk(VDimensia* d,VIndex nposition);
	void Init();
	void Update();
	void Render();
	void Destroy();
	VIndex GetPos();
	int GetX();
	int GetY();
	int GetZ();
	void Calculate();
};

//Voxel Dimension class.
class VDimensia
{
public:
	//The voxels current state. > 0==initialize : 1==update : 2==destroy <
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
	//The dimensions contructor.
	VDimensia(VManager* m,string nm);
	//The render method.
	void Render();
};

//Voxel Manager class.
class VManager
{
public:
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