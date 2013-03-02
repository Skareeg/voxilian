#ifndef VOX_H
#define VOX_H

#include "Types.h"
#include "Math.h"

//This is the standard size of a chunk.
#define VoxSize 14

//This is the MC Algorithm implementor.
int Polygonise(VoxelCell grid,double isolevel,std::vector<Triangle> *triangles);
//This interpolates (smooths) out the vectors.
Vector3 VertexInterp(float isolevel,Vector3 p1,Vector3 p2,float valp1,float valp2);
//This may or may not be used for normals.
Vector3 CrossProduct(Vector3 v1,Vector3 v2);
//This may or may not be used for normals.
Vector3 Normalize(Vector3 v);

class Voxel
{
public:
	//This is the triangular mesh of this voxel.
	std::vector<Triangle> mesh;

	//This is the density grid.
	float dgrid[VoxSize][VoxSize][VoxSize];

	//This is the cell grid. It should not be accessed directly.
	VoxelCell cells[VoxSize-1][VoxSize-1][VoxSize-1];

	//This is the voxels position.
	Vector3 pos;

	//This is this voxels local write position.
	Vector3 vwrite;

	//This is the voxel initiation code. It must be called.
	void Init(Vector3 position);

	//This is the marching cubes application code. Call to update from the density grid.
	void Calculate(float isolevel);

	//This is the voxel drawing code.
	void Draw();

	//This is the code to create spheres in the voxel.
	void VDSphere(Vector3 vpos, float radius, float density, bool solid);
};
#endif