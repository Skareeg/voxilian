#include "VoxelManager.h"
void VoxelManager::Init()
{
	vwrite=VMath::Vector(0,0,0);
	for(int i = 0;i<VXSize;i++)
	{
		for(int j = 0;j<VYSize;j++)
		{
			for(int k = 0;k<VZSize;k++)
			{
				Voxel vx;
				vx.Init(VMath::Vector(i*VoxSize,j*VoxSize,-k*VoxSize));
				Vector3 mp;
				mp.x=(VoxSize/2);
				mp.y=(VoxSize/2);
				mp.z=(VoxSize/2);
				for(int b = 0;b<VoxSize;b++)
				{
					for(int n = 0;n<VoxSize;n++)
					{
						for(int m = 0;m<VoxSize;m++)
						{
							Vector3 cp;
							cp.x=b;
							cp.y=n;
							cp.z=m;
							vx.dgrid[b][n][m]=VMath::Distance(cp,mp)/((float)VoxSize);
						}
					}
				}
				vx.Calculate(0.5f);
				voxels.push_back(vx);
			}
		}
	}
}
void VoxelManager::Update(Vector3 vpos)
{
	//Create the position inside the voxel the will draw. Must be local to the voxel.
	Vector3 cpos;
	cpos.x=Math::Remainder(vpos.x,VoxSize);
	cpos.y=Math::Remainder(vpos.y,VoxSize);
	cpos.z=Math::Remainder(vpos.z,VoxSize);
	for(int i = 0;i<voxels.size();i++)
	{
		voxels[i].vwrite=(vpos-voxels[i].pos);
	}
	this->vwrite=vpos;
}
void VoxelManager::Render()
{
	for(int i = 0;i<voxels.size();i++)
	{
		voxels[i].Draw();
	}
}
void VoxelManager::VDSphere(Vector3 vpos, float radius, float density, bool solid)
{
	//Go through each voxel.
	for(int b = 0;b<voxels.size();b++)
	{
		//If the voxel is closer to the player (vpos) by Voxsize*1.5, then do this.
		if(VMath::Distance(vpos,voxels[b].pos)<(float)VoxSize*1.5f)
		{
			//Create the position inside the voxel the will draw. Must be local to the voxel.
			Vector3 cpos;
			cpos.x=Math::Remainder(vpos.x,VoxSize);
			cpos.y=Math::Remainder(vpos.y,VoxSize);
			cpos.z=Math::Remainder(vpos.z,VoxSize);
			//Run the VoxelSphere code within the selected voxels.
			voxels[b].VDSphere(vwrite,radius,density,solid);
		}
	}
}