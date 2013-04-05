#include "Voxel.h"
#include "VoxelChunk.h"
void Voxel::Init(Vector3 position)
{
	vPosition=position;
}
void Voxel::Draw()
{
	//Move to the next draw location and draw the correct voxel representation.
	if(fDensity>VoxHold)
	{
		glPushMatrix();
		gTrans(-vPosition.x,-vPosition.y,-vPosition.z);
		if(nType==VOXTYPE_CUBE)
		{
			Draw::Cube(0,0,0);
		}
		glPopMatrix();
	}
}
void Voxel::Calculate()
{
	if(nType==VOXTYPE_TRIAG)
	{
		mesh.clear();
		int i = vPosition.x;
		int j = vPosition.y;
		int k = vPosition.z;
		vc.p[0]=VMath::Vector(i,j,k);
		vc.p[1]=VMath::Vector(i+1,j,k);
		vc.p[2]=VMath::Vector(i+1,j+1,k);
		vc.p[3]=VMath::Vector(i,j+1,k);
		vc.p[4]=VMath::Vector(i,j,k+1);
		vc.p[5]=VMath::Vector(i+1,j,k+1);
		vc.p[6]=VMath::Vector(i+1,j+1,k+1);
		vc.p[7]=VMath::Vector(i,j+1,k+1);
		vc.val[0]=vcVoxelChunk->vxVoxels[i][j][k].fDensity;
		vc.val[1]=vcVoxelChunk->vxVoxels[i+1][j][k].fDensity;
		vc.val[2]=vcVoxelChunk->vxVoxels[i+1][j+1][k].fDensity;
		vc.val[3]=vcVoxelChunk->vxVoxels[i][j+1][k].fDensity;
		vc.val[4]=vcVoxelChunk->vxVoxels[i][j][k+1].fDensity;
		vc.val[5]=vcVoxelChunk->vxVoxels[i+1][j][k+1].fDensity;
		vc.val[6]=vcVoxelChunk->vxVoxels[i+1][j+1][k+1].fDensity;
		vc.val[7]=vcVoxelChunk->vxVoxels[i][j+1][k+1].fDensity;
		VoxelFunc::Polygonise(vc,VoxHold,&mesh);
	}
	if(nType==VOXTYPE_CUBE)
	{
		mesh.clear();
		int i = vPosition.x;
		int j = vPosition.y;
		int k = vPosition.z;
	}
}