#include "Game.h"

void Game::Init()
{
	glS.Init(false);
	/*vx.Init(VMath::Vector(0,0,0));
	Vector3 mp;
	mp.x=VoxSize/2;
	mp.y=VoxSize/2;
	mp.z=VoxSize/2;
	for(int i = 0;i<VoxSize;i++)
	{
		for(int j = 0;j<VoxSize;j++)
		{
			for(int k = 0;k<VoxSize;k++)
			{
				Vector3 cp;
				cp.x=i;
				cp.y=j;
				cp.z=k;
				vx.dgrid[i][j][k]=VMath::Distance(cp,mp)/((float)VoxSize);
			}
		}
	}
	vx.Calculate(0.5f);*/
	voxelmanager.Init();
}
void Game::Render()
{
	//Draw from camera.
	glS.DrawBegin();
	//Draw voxels.
	//vx.Draw();
	voxelmanager.Render();
	glBegin(GL_TRIANGLES);
	glVertex3f(-1,-1,1);
	glVertex3f(1,-1,1);
	glVertex3f(1,1,1);
	glVertex3f(1,1,1);
	glVertex3f(1,-1,1);
	glVertex3f(-1,-1,1);
	glEnd();
	glS.DrawEnd();
}
void Game::Run()
{
	Vector3 v;
	v=glS.camera->pos;
	v.x=v.x;
	v.y=v.y;
	v.z=v.z;
	voxelmanager.Update(v);
	glS.FlyInput();
	if(glS.GetKey('R')==true)
	{
		voxelmanager.VDSphere(v,1,-0.1f,true);
	}
	/*if(glS.GetKey('F')==true)
	{
		Vector3 v;
		v=glS.camera->pos;
		v.x=-v.x;
		v.y=-v.y;
		v.z=-v.z;
		vx.VDSphere(v,1,0.1f,true);
	}*/
	//glS.Run is always called last
	glS.Run();
}
void Game::End()
{
	glS.Terminate();
}