// Voxilian.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <GL\glfw.h>
#include "Types.h"
#include "Voxel.h"
#include "Camera.h"
#include <ctime>
#include "GLSYS.h"

#define VSIZE 10

using namespace std;

float dworld[VSIZE][VSIZE][VSIZE];
float world[VSIZE][VSIZE][VSIZE];
VoxelCell vworld[VSIZE-1][VSIZE-1][VSIZE-1];
vector<Triangle> tworld;
vector<Vector3> nworld;
Camera fcam;
Vector3 sp;
float f;
float iso;

float PI()
{
	return 3.14159265359f;
}

float DegToRad(float x)
{
	return x*(PI()/180.0f);
}

Vector3 cpos;
Vector3 crot;
int ky[11];
int mm[2];

void CalculateVoxel()
{
	for(int i = 0;i<VSIZE-1;i++)
	{
		for(int j = 0;j<VSIZE-1;j++)
		{
			for(int k = 0;k<VSIZE-1;k++)
			{
				Vector3 cp;
				cp.x=i;
				cp.y=j;
				cp.z=k;
				vworld[i][j][k].p[0]=VMath::Vector(i,j,k);
				vworld[i][j][k].p[1]=VMath::Vector(i+1,j,k);
				vworld[i][j][k].p[2]=VMath::Vector(i+1,j+1,k);
				vworld[i][j][k].p[3]=VMath::Vector(i,j+1,k);
				vworld[i][j][k].p[4]=VMath::Vector(i,j,k+1);
				vworld[i][j][k].p[5]=VMath::Vector(i+1,j,k+1);
				vworld[i][j][k].p[6]=VMath::Vector(i+1,j+1,k+1);
				vworld[i][j][k].p[7]=VMath::Vector(i,j+1,k+1);
				vworld[i][j][k].val[0]=dworld[i][j][k];
				vworld[i][j][k].val[1]=dworld[i+1][j][k];
				vworld[i][j][k].val[2]=dworld[i+1][j+1][k];
				vworld[i][j][k].val[3]=dworld[i][j+1][k];
				vworld[i][j][k].val[4]=dworld[i][j][k+1];
				vworld[i][j][k].val[5]=dworld[i+1][j][k+1];
				vworld[i][j][k].val[6]=dworld[i+1][j+1][k+1];
				vworld[i][j][k].val[7]=dworld[i][j+1][k+1];
				Polygonise(vworld[i][j][k],iso,&tworld);
			}
		}
	}
	cout<<"There are "<<tworld.size()<<" triangles.\n";
}

void key(int ik,int is)
{
	//cout<<ik<<":"<<is<<"\n";
	//87-w
	//83-s
	//65-a
	//68-d
	if(ik=='W')
	{
		ky[0]=is;
	}
	if(ik=='S')
	{
		ky[1]=is;
	}
	if(ik=='A')
	{
		ky[2]=is;
	}
	if(ik=='D')
	{
		ky[3]=is;
	}
	if(ik==GLFW_KEY_SPACE)
	{
		ky[4]=is;
	}
	if(ik==GLFW_KEY_LSHIFT)
	{
		ky[5]=is;
	}
	if(ik=='R')
	{
		ky[6]=is;
	}
	if(ik=='F')
	{
		ky[7]=is;
	}
	if(ik=='Q')
	{
		ky[8]=is;
	}
	if(ik=='E')
	{
		ky[9]=is;
	}
	if(ik=='G')
	{
		ky[10]=is;
	}
}

void tmove(float* x,float n,float t)
{
	(*x)+=(n*(t));
}

float ttime()
{
	return ((float)clock())/CLOCKS_PER_SEC;
}

bool ss;

void MMouseMove(int mx,int my)
{
	if(ss==false)
	{
		mm[0]=mx-64;
		mm[1]=my-64;
		crot.y+=((float)mm[0]/2.0f);
		crot.x+=((float)mm[1]/2.0f);
		glfwSetMousePos(64,64);
	}
}

int main(int argc, char** argv)
{
	ss=false;
	iso=0.1f;
	float ts;
	ts=ttime();
	float tf;
	tf=0;
	f=0;
	sp.x=5;
	sp.y=5;
	sp.z=5;
	cpos.x=0;cpos.y=0;cpos.z=0;
	crot.x=0;crot.y=0;crot.z=0;
	fcam.pos=VMath::Vector(0,0,0);
	fcam.rot=VMath::Vector(0,0,0);
	Vector3 mp;
	mp.x=VSIZE/2;
	mp.y=0;
	mp.z=VSIZE/2;
	for(int i = 0;i<VSIZE;i++)
	{
		for(int j = 0;j<VSIZE;j++)
		{
			for(int k = 0;k<VSIZE;k++)
			{
				Vector3 cp;
				cp.x=i;
				cp.y=j;
				cp.z=k;
				dworld[i][j][k]=VMath::Distance(cp,mp)/((float)VSIZE);
			}
		}
	}
	CalculateVoxel();
	std::system("pause");
	glfwInit();
	glfwOpenWindow(640,480,0,0,0,0,24,0,GLFW_WINDOW);
	glfwSetMousePos(64,64);
	glfwSetKeyCallback(key);
	glfwSetMousePosCallback(MMouseMove);
	glEnable(GL_DEPTH_TEST);
	glfwDisable(GLFW_MOUSE_CURSOR);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
	while(glfwGetKey(GLFW_KEY_ESC)==GL_FALSE&&glfwGetWindowParam(GLFW_OPENED)==GL_TRUE)
	{
		glMatrixMode(GL_MODELVIEW_MATRIX);
		glClearColor(0,0.1f,0,1);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluPerspective(60.0f,1,0.1,100.0f);
		glRotatef(crot.x,1,0,0);
		glRotatef(crot.y,0,1,0);
		glRotatef(crot.z,0,0,1);
		glTranslatef(cpos.x,cpos.y,cpos.z-5.0f);
		glBegin(GL_TRIANGLES);
		glVertex3f(-1,-1,1);
		glVertex3f(1,-1,1);
		glVertex3f(1,1,1);
		glVertex3f(1,1,1);
		glVertex3f(1,-1,1);
		glVertex3f(-1,-1,1);
		for(int i = 0;i<tworld.size();i++)
		{
			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(tworld[i].p[0].x,tworld[i].p[0].y,tworld[i].p[0].z);
			glColor3f(0.0f,1.0f,0.0f);
			glVertex3f(tworld[i].p[1].x,tworld[i].p[1].y,tworld[i].p[1].z);
			glColor3f(0.0f,0.0f,1.0f);
			glVertex3f(tworld[i].p[2].x,tworld[i].p[2].y,tworld[i].p[2].z);
		}
		float spd;
		spd=1.0f;
		if(ky[0]==1)
		{
			tmove(&cpos.z,spd*(cos(DegToRad(crot.y))),tf);
			tmove(&cpos.x,spd*(-sin(DegToRad(crot.y))),tf);
			tmove(&cpos.y,spd*(sin(DegToRad(crot.x))),tf);
			cout<<"Z:"<<cpos.z<<"\n";
		}
		if(ky[1]==1)
		{
			tmove(&cpos.z,-spd*(cos(DegToRad(crot.y))),tf);
			tmove(&cpos.x,-spd*(-sin(DegToRad(crot.y))),tf);
			tmove(&cpos.y,-spd*(sin(DegToRad(crot.x))),tf);
			cout<<"Z:"<<cpos.z<<"\n";
		}
		if(ky[2]==1)
		{
			tmove(&cpos.z,spd*(cos(DegToRad(crot.y-90.0f))),tf);
			tmove(&cpos.x,spd*(-sin(DegToRad(crot.y-90.0f))),tf);
			cout<<"X:"<<cpos.x<<"\n";
		}
		if(ky[3]==1)
		{
			tmove(&cpos.z,-spd*(cos(DegToRad(crot.y-90.0f))),tf);
			tmove(&cpos.x,-spd*(-sin(DegToRad(crot.y-90.0f))),tf);
			cout<<"X:"<<cpos.x<<"\n";
		}
		if(ky[4]==1)
		{
			tmove(&cpos.y,-spd,tf);
			cout<<"Y:"<<cpos.y<<"\n";
		}
		if(ky[5]==1)
		{
			tmove(&cpos.y,spd,tf);
			cout<<"Y:"<<cpos.y<<"\n";
		}
		if(ky[6]==1)
		{
			tworld.clear();
			iso+=0.001f;
			CalculateVoxel();
		}
		if(ky[7]==1)
		{
			tworld.clear();
			iso-=0.001f;
			CalculateVoxel();
		}
		if(ky[10]==1)
		{
			ss=true;
			glfwEnable(GLFW_MOUSE_CURSOR);
		}
		glEnd();
		glfwSwapBuffers();
		tf=(ttime()-ts);
		ts=ttime();
		glfwGetTime();
	}
	glfwCloseWindow();
	glfwTerminate();
	return 0;
}
