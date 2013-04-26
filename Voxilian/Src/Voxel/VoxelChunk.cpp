#include "VoxelChunk.h"
#include "VoxelManager.h"
VoxelChunk::VoxelChunk()
{
	good=false;
}
void VoxelChunk::Init(Vector3 position)
{
	vPosition=position;
	vWrite=VMath::Vector(0,0,0);
	for(int i = 0;i<VoxSize;i++)
	{
		for(int j = 0;j<VoxSize;j++)
		{
			for(int k = 0;k<VoxSize;k++)
			{
				vxVoxels[i][j][k].Init(VMath::Vector(i,j,k));
			}
		}
	}
	vthis=this;
	vWPosition.x=position.x*VoxSize;
	vWPosition.y=position.y*VoxSize;
	vWPosition.z=position.z*VoxSize;
	good=true;
}
void VoxelChunk::Calculate()
{
	vWPosition.x=vPosition.x*VoxSize;
	vWPosition.y=vPosition.y*VoxSize;
	vWPosition.z=vPosition.z*VoxSize;
	numvc=0;
	for(int i = 0;i<3;i++)
	{
		for(int j = 0;j<3;j++)
		{
			for(int k = 0;k<3;k++)
			{
				vc[i][j][k]=NULL;
				vce[i][j][k]=0;
				for(int b = 0;b<vm->voxels.size();b++)
				{
					if((int)vm->voxels[b].vPosition.x==(int)vPosition.x+(i-1))
					{
						if((int)vm->voxels[b].vPosition.y==(int)vPosition.y+(j-1))
						{
							if((int)vm->voxels[b].vPosition.z==(int)vPosition.z+(k-1))
							{
								vc[i][j][k]=&(vm->voxels[b]);
								vce[i][j][k]=1;
								numvc++;
							}
						}
					}
				}
			}
		}
	}
	for(int i = 0;i<VoxSize;i++)
	{
		for(int j = 0;j<VoxSize;j++)
		{
			for(int k = 0;k<VoxSize;k++)
			{
				vxVoxels[i][j][k].vcVoxelChunk=this;
			}
		}
	}
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
void VoxelChunk::ChunkCalculate(int i,int j,int k)
{
	vc[i][j][k]=NULL;
	vce[i][j][k]=0;
	for(int b = 0;b<vm->voxels.size();b++)
	{
		if((int)vm->voxels[b].vPosition.x==(int)vPosition.x+(i-1))
		{
			if((int)vm->voxels[b].vPosition.y==(int)vPosition.y+(j-1))
			{
				if((int)vm->voxels[b].vPosition.z==(int)vPosition.z+(k-1))
				{
					vc[i][j][k]=&(vm->voxels[b]);
					vce[i][j][k]=1;
					numvc++;
				}
			}
		}
	}
}
void VoxelChunk::PreCalculate(int i,int j,int k)
{
	vxVoxels[i][j][k].vcVoxelChunk=this;
}
void VoxelChunk::CalculateS(int i,int j,int k)
{
	vxVoxels[i][j][k].Calculate();
}
void VoxelChunk::Draw()
{
	glPushMatrix();
	glTranslatef(vWPosition.x,vWPosition.y,vWPosition.z);
			if(vPosition.x==0&&vPosition.y==0&&vPosition.z==0)
			{
				glPushMatrix();
				glScalef(0.1,2,0.1);
				Draw::Cube(0,0,0);
				glPopMatrix();
			}
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
	for(int i = 0;i<=VoxSize;i++)
	{
		for(int j = 0;j<=VoxSize;j++)
		{
			for(int k = 0;k<=VoxSize;k++)
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
					if(i<VoxSize)
					{
						if(j<VoxSize)
						{
							if(k<VoxSize)
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
void VoxelChunk::CallUpdate()
{
	/*CallItem call = g_cmd.GetNextCall("main");
	if(call.ID>=0)
	{
		if(call.type=="VoxelChunkInit")
		{
			if(call.xint[0]==ID)
			{
				//Set the state.
				state=VOXELCHUNKSTATE::Calculating;
				//StartPreinit
				vWPosition.x=vPosition.x*VoxSize;
				vWPosition.y=vPosition.y*VoxSize;
				vWPosition.z=vPosition.z*VoxSize;
				numvc=0;
				//EndPreinit
				std::vector<int> args1;
				std::vector<float> args2;
				args1.push_back(ID);
				args1.push_back(0);
				args1.push_back(0);
				args1.push_back(0);
				g_cmd.Call("main","VCCI",args1,args2);
			}
		}
		if(call.type=="VCCI")
		{
			if(call.xint[0]==ID)
			{
				vxVoxels[call.xint[1]][call.xint[2]][call.xint[3]].Init(VMath::Vector(call.xint[1],call.xint[2],call.xint[3]));
				call.xint[3]++;
				if(call.xint[3]>=3)
				{
					call.xint[3]=0;
					call.xint[2]++;
				}
				if(call.xint[2]>=3)
				{
					call.xint[2]=0;
					call.xint[1]++;
				}
				if(call.xint[1]>=3)
				{
					std::vector<int> args1;
					std::vector<float> args2;
					args1.push_back(ID);
					args1.push_back(0);
					args1.push_back(0);
					args1.push_back(0);
					g_cmd.Call("main","VCVI",args1,args2);
				}
				else
				{
					g_cmd.Call("main",call);
				}
			}
		}
		if(call.type=="VCVI")
		{
			if(call.xint[0]==ID)
			{
				PreCalculate(call.xint[1],call.xint[2],call.xint[3]);
				call.xint[3]++;
				if(call.xint[3]>=VoxSize)
				{
					call.xint[3]=0;
					call.xint[2]++;
				}
				if(call.xint[2]>=VoxSize)
				{
					call.xint[2]=0;
					call.xint[1]++;
				}
				if(call.xint[1]>=VoxSize)
				{
					std::vector<int> args1;
					std::vector<float> args2;
					args1.push_back(ID);
					args1.push_back(0);
					args1.push_back(0);
					args1.push_back(0);
					g_cmd.Call("main","VCVC",args1,args2);
				}
				else
				{
					g_cmd.Call("main",call);
				}
			}
		}
		if(call.type=="VCVC")
		{
			if(call.xint[0]==ID)
			{
				CalculateS(call.xint[1],call.xint[2],call.xint[3]);
				call.xint[3]++;
				if(call.xint[3]>=VoxSize)
				{
					call.xint[3]=0;
					call.xint[2]++;
				}
				if(call.xint[2]>=VoxSize)
				{
					call.xint[2]=0;
					call.xint[1]++;
				}
				if(call.xint[1]>=VoxSize)
				{
					state=VOXELCHUNKSTATE::Idle;
				}
				else
				{
					g_cmd.Call("main",call);
				}
			}
		}
	}*/
}
void VoxelChunk::CallCalc()
{
}