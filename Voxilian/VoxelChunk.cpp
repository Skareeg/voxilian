#include "VoxelChunk.h"
void VoxelChunk::Init(Vector3 position)
{
	vPosition=position;
	vWrite=VMath::Vector(0,0,0);
	for(int i = 0;i<=VoxSize;i++)
	{
		for(int j = 0;j<=VoxSize;j++)
		{
			for(int k = 0;k<=VoxSize;k++)
			{
				vxVoxels[i][j][k].Init(VMath::Vector(i,j,k));
				vxVoxels[i][j][k].vcVoxelChunk=this;
			}
		}
	}
}
void VoxelChunk::Calculate()
{
	for(int i = 0;i<VoxSize;i++)
	{
		for(int j = 0;j<VoxSize;j++)
		{
			for(int k = 0;k<VoxSize;k++)
			{
				vxVoxels[i][j][k].Calculate();
			}
		}
	}
}
void VoxelChunk::Draw()
{
	glPushMatrix();
	glTranslatef(-vPosition.x,-vPosition.y,-vPosition.z);
	//Draw Code Here.
	for(int i = 0;i<VoxSize;i++)
	{
		for(int j = 0;j<VoxSize;j++)
		{
			for(int k = 0;k<VoxSize;k++)
			{
				vxVoxels[i][j][k].Draw();
			}
		}
	}
	glPopMatrix();
}
void VoxelChunk::VDSphere(float radius, float density, bool solid)
{
	//Go through each voxel point.
	for(int i = 0;i<VoxSize;i++)
	{
		for(int j = 0;j<VoxSize;j++)
		{
			for(int k = 0;k<VoxSize;k++)
			{
				//Get the distance between the player (vpos) and the voxel point.
				float distance = VMath::Distance(vWrite,VMath::Vector(i,j,k));
				//If the distance is in the radius, then do this.
				if(distance<radius)
				{
					//If solid is stated true, then subtract the density on all points equally.
					//Otherwise, subtract it with the power of subtraction closer to the vpos.
					if(solid==true)
					{
						vxVoxels[i][j][k].fDensity-=density;
					}
					else
					{
						vxVoxels[i][j][k].fDensity-=((1-(distance/radius))*density);
					}
					if(i<=VoxSize)
					{
						if(j<=VoxSize)
						{
							if(k<=VoxSize)
							{
								vxVoxels[i][j][k].Calculate();
							}
						}
					}
				}
			}
		}
	}
}