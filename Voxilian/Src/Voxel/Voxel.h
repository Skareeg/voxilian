#ifndef VOXEL_H
#define VOXEL_H

#include "..\Utilities\Types.h"
#include "..\Utilities\Math.h"
#include "..\Utilities\GLSYS.h"

//This is the threshold value for the chunk.
#define VoxHold 0.5f
//This is the standard size of a chunk.
#define VoxSize 3

//These are the types of voxels available.
#define VOXTYPE_TRIAG 0
#define VOXTYPE_CUBE 1
#define VOXTYPE_HEX 2

class VoxelChunk;

class Voxel
{
public:
	//This defines the type of voxel.
	int nType;

	//This is the density grid.
	float fDensity;

	//This is the voxels position.
	Vector3 vPosition;

	//This is the drawing side listing.
	int sides[6];

	//This is the voxels chunk.
	VoxelChunk* vcVoxelChunk;

	//This is the voxels associated gridcell.
	VoxelCell vc;

	//This is the triangular mesh of this voxel, if used.
	std::vector<Triangle> mesh;

	//This is the voxel initiation code. It must be called.
	void Init(Vector3 position);

	//This is the MC calcuation code.
	void Calculate();

	//This is the voxel drawing code.
	void Draw();
};
#endif