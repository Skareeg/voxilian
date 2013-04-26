#include "VoxelManager.h"
#include <thread>
#include <mutex>
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
				voxels.push_back(*(new VoxelChunk()));
				voxels.back().Init(VMath::Vector(i,j,k));
				voxels.back().vm=this;
				for(int a = 0;a<VoxSize;a++)
				{
					for(int b = 0;b<VoxSize;b++)
					{
						voxels.back().vxVoxels[a][0][b].fDensity=1.0f;
					}
				}
			}
		}
	}
	for(int b = 0;b<voxels.size();b++)
	{
		thread t = thread(&VoxelChunk::Calculate,&voxels[b]);
		t.join();
	}
	ind=0;
	good=true;
}
void createVox(VoxelManager* vm,Vector3 vpos,bool* g)
{
	int ix = vpos.x/VoxSize;
	int iy = vpos.y/VoxSize;
	int iz = vpos.z/VoxSize;
	for(int i = -2;i<=2;i++)
	{
		for(int j = -2;j<=2;j++)
		{
			for(int k = -2;k<=2;k++)
			{
				//Check at the positions around the player for free chunk locations.
				int px = ix+i;
				int py = iy+j;
				int pz = iz+k;
				px=floor(px);
				py=floor(py);
				pz=floor(pz);
				float distToPly = VMath::Distance(VMath::Vector(ix,iy,iz),VMath::Vector(ix+i,iy+j,iz+k));
				if(distToPly<3)
				{
					bool good = true;
					for(int b = 0;b<vm->voxels.size();b++)
					{
						if((int)vm->voxels[b].vPosition.x==px&&(int)vm->voxels[b].vPosition.y==py&&(int)vm->voxels[b].vPosition.z==pz)
						{
							good=false;
						}
					}
					if(good==true)
					{
						vm->voxels.push_back(*(new VoxelChunk()));
						vm->voxels.back().Init(VMath::Vector(i,j,k));
						//thread th = thread(&VoxelChunk::Init,&(voxels.back()),VMath::Vector(i,j,k));
						//th.detach();
						vm->voxels.back().vm=vm;
						for(int a = 0;a<VoxSize;a++)
						{
							for(int b = 0;b<VoxSize;b++)
							{
								vm->voxels.back().vxVoxels[a][0][b].fDensity=1.0f;
							}
						}
						for(int b = 0;b<vm->voxels.size();b++)
						{
							//thread t = thread(&VoxelChunk::Calculate,&voxels[b]);
							//t.detach();
							vm->voxels[b].Calculate();
						}
					}
				}
			}
		}
	}
	*g=true;
}
void VoxelManager::Update(Vector3 vpos)
{
	//Create the position inside the voxel the will draw. Must be local to the voxel.
	Vector3 cpos;

	int ix = vpos.x/VoxSize;
	int iy = vpos.y/VoxSize;
	int iz = vpos.z/VoxSize;

	//Go through each voxel.
	for(int b = 0;b<voxels.size();b++)
	{
		float distToPly = VMath::Distance(VMath::Vector(ix,iy,iz),voxels[b].vPosition);
		voxels[b].vWrite=(cpos-voxels[b].vWPosition);
		if(distToPly>5)
		{
			voxels.erase(voxels.begin()+b);
		}
	}
	if(good==true)
	{
		thread t = thread(&createVox,this,vpos,&good);
		t.detach();
		good=false;
	}
	/*for(int i = -2;i<=2;i++)
	{
		for(int j = -2;j<=2;j++)
		{
			for(int k = -2;k<=2;k++)
			{
				//Check at the positions around the player for free chunk locations.
				int px = ix+i;
				int py = iy+j;
				int pz = iz+k;
				px=floor(px);
				py=floor(py);
				pz=floor(pz);
				float distToPly = VMath::Distance(VMath::Vector(ix,iy,iz),VMath::Vector(ix+i,iy+j,iz+k));
				if(distToPly<3)
				{
					bool good = true;
					for(int b = 0;b<voxels.size();b++)
					{
						if((int)voxels[b].vPosition.x==px&&(int)voxels[b].vPosition.y==py&&(int)voxels[b].vPosition.z==pz)
						{
							good=false;
						}
					}
					if(good==true)
					{
						voxels.push_back(*(new VoxelChunk()));
						voxels.back().Init(VMath::Vector(i,j,k));
						//thread th = thread(&VoxelChunk::Init,&(voxels.back()),VMath::Vector(i,j,k));
						//th.detach();
						voxels.back().vm=this;
						for(int a = 0;a<VoxSize;a++)
						{
							for(int b = 0;b<VoxSize;b++)
							{
								voxels.back().vxVoxels[a][0][b].fDensity=1.0f;
							}
						}
						for(int b = 0;b<voxels.size();b++)
						{
							//thread t = thread(&VoxelChunk::Calculate,&voxels[b]);
							//t.detach();
							voxels[b].Calculate();
						}
					}
				}
			}
		}
	}*/
	this->vwrite=vpos;
}
void VoxelManager::Render()
{
	//Render each voxel.
	for(int i = 0;i<voxels.size();i++)
	{
		if(voxels[i].good==true)
		{
			voxels[i].Draw();
		}
	}
}
void VoxelManager::VDSphere(Vector3 vpos, float radius, float density, bool solid)
{
	//Go through each voxel.
	for(int b = 0;b<voxels.size();b++)
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
	}
}