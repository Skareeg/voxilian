#ifndef VOXC_H
#define VOXC_H

#include "..\Utilities\Types.h"
#include "Math.h"
#include "..\Utilities\GLSYS.h"
#include "Voxel.h"
#include "..\Utilities\CMDCall.h"
#include <thread>

class VoxelManager;

enum VOXELCHUNKSTATE
{
	Idle,
	Calculating
};

class VoxelChunk
{
public:
	//These are the voxel chunks neighbors.
	VoxelChunk* vc[3][3][3];
	int vce[3][3][3];
	int numvc;
	VoxelChunk* vthis;

	//These are the voxels themselves.
	Voxel vxVoxels[VoxSize][VoxSize][VoxSize];

	//This is the voxels Index position.
	Vector3 vPosition;

	//This is the voxels World position.
	Vector3 vWPosition;

	//This is this voxels local write position.
	Vector3 vWrite;

	//This is the chunks manager.
	VoxelManager* vm;

	VoxelChunk();

	//This is the voxel initiation code. It must be called.
	void Init(Vector3 position);

	//This is the marching cubes application code. Call to update from the density grid.
	void Calculate();

	//This is the voxel drawing code.
	void Draw();

	//This is the code to create spheres in the voxel.
	void VDSphere(float radius, float density, bool solid);

	//This is the VC's ID.
	int ID;

	//This is the VC's state.
	int state;

	//Whether or not it is good.
	bool good;

	//This is the update function.
	void CallUpdate();

	//Calculates the neighbor chunks.
	void ChunkCalculate(int i,int j,int k);

	//Sets all voxels to this chunk.
	void PreCalculate(int i,int j,int k);

	//Calculates a specific voxel.
	void CalculateS(int i,int j,int k);

	//Calls the calculate in a thread.
	void CallCalc();
};
#endif