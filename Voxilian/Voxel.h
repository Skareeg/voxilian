#ifndef VOX_H
#define VOX_H
#include "Types.h"
#define VoxSize 10
int Polygonise(VoxelCell grid,double isolevel,std::vector<Triangle> *triangles);
Vector3 VertexInterp(float isolevel,Vector3 p1,Vector3 p2,float valp1,float valp2);
Vector3 CrossProduct(Vector3 v1,Vector3 v2);
Vector3 Normalize(Vector3 v);
class Voxel
{
public:
	std::vector<Triangle> mesh;
	float dgrid[VoxSize][VoxSize][VoxSize];
	VoxelCell cells[VoxSize-1][VoxSize-1][VoxSize-1];
	Vector3 pos;
	void Init(Vector3 position);
	void Calculate(float isolevel);
	void Draw();
};
#endif