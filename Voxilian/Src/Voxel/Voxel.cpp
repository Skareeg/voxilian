#include "Voxel.h"
#include "VoxelChunk.h"
void Voxel::Init(Vector3 position)
{
	vPosition=position;
	nType=VOXTYPE_CUBE;
	fDensity=0.0f;
	sides[0]=1;
	sides[1]=1;
	sides[2]=1;
	sides[3]=1;
	sides[4]=1;
	sides[5]=1;
}
void Voxel::Draw()
{
	//Move to the next draw location and draw the correct voxel representation.
	if(fDensity>0.0f)
	{
		glPushMatrix();
		glTranslatef(vPosition.x,vPosition.y,vPosition.z);
		if(nType==VOXTYPE_CUBE)
		{
			Draw::CubeSide(0,0,0,
				sides[DRAW_CUBE_DOWN],sides[DRAW_CUBE_UP],
				sides[DRAW_CUBE_LEFT],sides[DRAW_CUBE_RIGHT],
				sides[DRAW_CUBE_BACKWARD],sides[DRAW_CUBE_FORWARD]);
			//
			glBegin(GL_LINES);
			//
			glColor3f(1,1,1);
			////
			glVertex3f(0,0,0);
			glVertex3f(1,0,0);
			//
			glVertex3f(0,1,0);
			glVertex3f(1,1,0);
			//
			glVertex3f(0,0,1);
			glVertex3f(1,0,1);
			//
			glVertex3f(0,1,1);
			glVertex3f(1,1,1);
			////
			glVertex3f(0,0,0);
			glVertex3f(0,1,0);
			//
			glVertex3f(1,0,0);
			glVertex3f(1,1,0);
			//
			glVertex3f(0,0,1);
			glVertex3f(0,1,1);
			//
			glVertex3f(1,0,1);
			glVertex3f(1,1,1);
			////
			glVertex3f(0,0,0);
			glVertex3f(0,0,1);
			//
			glVertex3f(1,0,0);
			glVertex3f(1,0,1);
			//
			glVertex3f(0,1,0);
			glVertex3f(0,1,1);
			//
			glVertex3f(1,1,0);
			glVertex3f(1,1,1);
			////
			glEnd();
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
		int i = vPosition.x;
		int j = vPosition.y;
		int k = vPosition.z;
		sides[0]=1;
		sides[1]=1;
		sides[2]=1;
		sides[3]=1;
		sides[4]=1;
		sides[5]=1;
		//DOWN
		if(j==0)
		{
			//Check to see if the voxel chunk below is there.
			if(vcVoxelChunk->vce[1][0][1]==1)
			{
				//Check the voxel below this voxel that exists within the chunk below.
				if(vcVoxelChunk->vc[1][0][1]->vxVoxels[i][VoxSize-1][k].fDensity>0.0f)
				{
					sides[DRAW_CUBE_DOWN]=0;
				}
			}
		}
		//UP
		if(j>=VoxSize-1)
		{
			//Check to see if the voxel chunk below is there.
			if(vcVoxelChunk->vce[1][2][1]==1)
			{
				//Check the voxel below this voxel that exists within the chunk below.
				if(vcVoxelChunk->vc[1][2][1]->vxVoxels[i][0][k].fDensity>0.0f)
				{
					sides[DRAW_CUBE_UP]=0;
				}
			}
		}
		//MID
		if(j>0)
		{
			if(vcVoxelChunk->vxVoxels[i][j-1][k].fDensity>0.0f)
			{
				sides[DRAW_CUBE_DOWN]=0;
			}
		}
		if(j<VoxSize-1)
		{
			if(vcVoxelChunk->vxVoxels[i][j+1][k].fDensity>0.0f)
			{
				sides[DRAW_CUBE_UP]=0;
			}
		}
		//LEFT
		if(i==0)
		{
			//Check to see if the voxel chunk below is there.
			if(vcVoxelChunk->vce[0][1][1]==1)
			{
				//Check the voxel below this voxel that exists within the chunk below.
				if(vcVoxelChunk->vc[0][1][1]->vxVoxels[VoxSize-1][j][k].fDensity>0.0f)
				{
					sides[DRAW_CUBE_LEFT]=0;
				}
			}
		}
		//RIGHT
		if(i>=VoxSize-1)
		{
			//Check to see if the voxel chunk below is there.
			if(vcVoxelChunk->vce[2][1][1]==1)
			{
				//Check the voxel below this voxel that exists within the chunk below.
				if(vcVoxelChunk->vc[2][1][1]->vxVoxels[0][j][k].fDensity>0.0f)
				{
					sides[DRAW_CUBE_RIGHT]=0;
				}
			}
		}
		//MID
		if(i>0)
		{
			if(vcVoxelChunk->vxVoxels[i-1][j][k].fDensity>0.0f)
			{
				sides[DRAW_CUBE_LEFT]=0;
			}
		}
		if(i<VoxSize-1)
		{
			if(vcVoxelChunk->vxVoxels[i+1][j][k].fDensity>0.0f)
			{
				sides[DRAW_CUBE_RIGHT]=0;
			}
		}
		//BACKWARD
		if(k==0)
		{
			//Check to see if the voxel chunk below is there.
			if(vcVoxelChunk->vce[1][1][0]==1)
			{
				//Check the voxel below this voxel that exists within the chunk below.
				if(vcVoxelChunk->vc[1][1][0]->vxVoxels[i][j][VoxSize-1].fDensity>0.0f)
				{
					sides[DRAW_CUBE_BACKWARD]=0;
				}
			}
		}
		//FORWARD
		if(k>=VoxSize-1)
		{
			//Check to see if the voxel chunk below is there.
			if(vcVoxelChunk->vce[1][1][2]==1)
			{
				//Check the voxel below this voxel that exists within the chunk below.
				if(vcVoxelChunk->vc[1][1][2]->vxVoxels[i][j][0].fDensity>0.0f)
				{
					sides[DRAW_CUBE_FORWARD]=0;
				}
			}
		}
		//MID
		if(k>0)
		{
			if(vcVoxelChunk->vxVoxels[i][j][k-1].fDensity>0.0f)
			{
				sides[DRAW_CUBE_BACKWARD]=0;
			}
		}
		if(k<VoxSize-1)
		{
			if(vcVoxelChunk->vxVoxels[i][j][k+1].fDensity>0.0f)
			{
				sides[DRAW_CUBE_FORWARD]=0;
			}
		}
	}
}