#include "VoxelManager.h"
void VoxelManager::Init()
{
	//Set initial vwrite to zero.
	vwrite=VMath::Vector(0,0,0);
	//Go through each voxel and create semi-spheres with them.
	for(int i = 0;i<VXSize;i++)
	{
		for(int j = 0;j<VYSize;j++)
		{
			for(int k = 0;k<VZSize;k++)
			{
				VoxelChunk vc;
				vc.Init(VMath::Vector(i,j,k));
				for(int a = 0;a<14;a++)
				{
					for(int b = 0;b<14;b++)
					{
						//vc.vxVoxels[a][0][b].fDensity=1.0f;
						//vc.vxVoxels[a][1][b].fDensity=1.0f;
					}
				}
				vc.Calculate();
				voxels.push_back(vc);
			}
		}
	}
}
void VoxelManager::Update(Vector3 vpos)
{
	//Create the position inside the voxel the will draw. Must be local to the voxel.
	Vector3 cpos;
	//Go through each voxel.
	/*for(int b = 0;b<voxels.size();b++)
	{
		voxels[b].vWrite=(cpos-voxels[b].vPosition);
	}*/
	this->vwrite=vpos;
}
void VoxelManager::Render()
{
	//Render each voxel.
	/*for(int i = 0;i<voxels.size();i++)
	{
		voxels[i].Draw();
	}*/
}
void VoxelManager::VDSphere(Vector3 vpos, float radius, float density, bool solid)
{
	//Go through each voxel.
	/*for(int b = 0;b<voxels.size();b++)
	{
		//If the voxel is closer to the player (vpos) by Voxsize*1.5, then do this.
		if(VMath::Distance(vpos,voxels[b].vPosition)<(float)VoxSize*1.5f)
		{
			//Create the position inside the voxel the will draw. Must be local to the voxel.
			Vector3 cpos;
			cpos=(vpos-voxels[b].vPosition);
			voxels[b].vWrite=cpos;
			//Run the VoxelSphere code within the selected voxels.
			voxels[b].VDSphere(radius,density,solid);
		}
	}*/
}