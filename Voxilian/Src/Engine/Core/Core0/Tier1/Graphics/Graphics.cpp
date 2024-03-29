#include "Graphics.h"

float cF(float f,float a)
{
	f+=(a*Graphics.deltaTime);
	return f;
}

CCamera::CCamera()
{
	CEntity::CEntity();
	fieldOfView=60.0f;
	aspectRatio=4.0f/3.0f;
	nearZ=0.1f;
	farZ=1000.0f;
	position=btVector3(0,0,0);
	euler=btVector3(0,0,0);
	rotation.setEuler(0,0,0);
	useQuat=false;
}
void CCamera::Init(string newname)
{
	CEntity::Init(newname);
	SetType("CCamera");
}

void CDrawPure::DrawQuad(btVector3* points,btVector3& color)
{
	glColor3f(color.x(),color.y(),color.z());
	glVertex3f(points[0].x(),points[0].y(),points[0].z());
	glVertex3f(points[1].x(),points[1].y(),points[1].z());
	glVertex3f(points[2].x(),points[2].y(),points[2].z());
	glVertex3f(points[0].x(),points[0].y(),points[0].z());
	glVertex3f(points[2].x(),points[2].y(),points[2].z());
	glVertex3f(points[3].x(),points[3].y(),points[3].z());
}
void CDraw::DrawRect(float px,float py,float sx,float sy,float depth)
{
	float rx = Graphics.resolution_x;
	float ry = Graphics.resolution_y;
	glBegin(GL_QUADS);
	glColor4f(1,1,1,1);
	float dpx[4] = 
	{
		(px),
		((px+sx)),
		((px+sx)),
		(px)
	};
	float dpy[4] = 
	{
		ry-((py+sy)),
		ry-((py+sy)),
		ry-(py),
		ry-(py)
	};
	glTexCoord2f(0,0);
	glVertex3f(dpx[0],dpy[3],depth);
	glTexCoord2f(1,0);
	glVertex3f(dpx[1],dpy[2],depth);
	glTexCoord2f(1,1);
	glVertex3f(dpx[2],dpy[1],depth);
	glTexCoord2f(0,1);
	glVertex3f(dpx[3],dpy[0],depth);
	glEnd();
}
void CDraw::DrawRect(float px,float py,float sx,float sy,unsigned int texture,float depth)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	DrawRect(px,py,sx,sy,depth);
}
void CDraw::DrawRect(float px,float py,float sx,float sy,float tpx,float tpy,float tsx,float tsy,unsigned int texture,float depth)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	float rx = Graphics.resolution_x;
	float ry = Graphics.resolution_y;
	glBegin(GL_QUADS);
	glColor4f(1,1,1,1);
	float dpx[4] = 
	{
		(px),
		((px+sx)),
		((px+sx)),
		(px)
	};
	float dpy[4] = 
	{
		ry-((py+sy)),
		ry-((py+sy)),
		ry-(py),
		ry-(py)
	};

	glTexCoord2f(tpx,tpy);
	glVertex3f(dpx[0],dpy[3],depth);
	
	glTexCoord2f(tsx,tpy);
	glVertex3f(dpx[1],dpy[2],depth);
	
	glTexCoord2f(tsx,tsy);
	glVertex3f(dpx[2],dpy[1],depth);
	
	glTexCoord2f(tpx,tsy);
	glVertex3f(dpx[3],dpy[0],depth);

	glEnd();
}
void CDraw::DrawQuad(btVector3* points,btVector3& color)
{
	glBegin(GL_TRIANGLES);
	pure.DrawQuad(points,color);
	glEnd();
}
void CDraw::DrawCube(btVector3& pos,float size)
{
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D,0);
	float px = pos.x();
	float py = pos.y();
	float pz = pos.z();
	float s = size;
	//..........................................................
	//Draw Cube Code Here
	//..........................................................
	btVector3 points[4];
	btVector3 color;
	glBegin(GL_TRIANGLES);
	//SIDE0 - Front
	color=btVector3(1,0,0);
	points[0]=btVector3(px-s,py-s,pz-s);
	points[1]=btVector3(px+s,py-s,pz-s);
	points[2]=btVector3(px+s,py+s,pz-s);
	points[3]=btVector3(px-s,py+s,pz-s);
	pure.DrawQuad(points,color);
	//SIDE1 - Back
	color=btVector3(1,1,0);
	points[0]=btVector3(px-s,py-s,pz+s);
	points[1]=btVector3(px+s,py-s,pz+s);
	points[2]=btVector3(px+s,py+s,pz+s);
	points[3]=btVector3(px-s,py+s,pz+s);
	pure.DrawQuad(points,color);
	//SIDE2 - Left
	color=btVector3(0,1,0);
	points[0]=btVector3(px-s,py-s,pz-s);
	points[1]=btVector3(px-s,py+s,pz-s);
	points[2]=btVector3(px-s,py+s,pz+s);
	points[3]=btVector3(px-s,py-s,pz+s);
	pure.DrawQuad(points,color);
	//SIDE3 - Right
	color=btVector3(0,1,1);
	points[0]=btVector3(px+s,py-s,pz-s);
	points[1]=btVector3(px+s,py+s,pz-s);
	points[2]=btVector3(px+s,py+s,pz+s);
	points[3]=btVector3(px+s,py-s,pz+s);
	pure.DrawQuad(points,color);
	//SIDE4 - Top
	color=btVector3(0,0,1);
	points[0]=btVector3(px-s,py-s,pz-s);
	points[1]=btVector3(px+s,py-s,pz-s);
	points[2]=btVector3(px+s,py-s,pz+s);
	points[3]=btVector3(px-s,py-s,pz+s);
	pure.DrawQuad(points,color);
	//SIDE5 - Bottom
	color=btVector3(1,0,1);
	points[0]=btVector3(px-s,py+s,pz-s);
	points[1]=btVector3(px+s,py+s,pz-s);
	points[2]=btVector3(px+s,py+s,pz+s);
	points[3]=btVector3(px-s,py+s,pz+s);
	pure.DrawQuad(points,color);
	glEnd();
}

CText::CText()
{
	font=0;
}
void CText::Init(string newfont)
{
	font=Graphics.LoadTexture(newfont,true);
}
void CText::Draw(float px,float py,float depth,string text)
{
	glPushMatrix();
	Graphics.Orthographic();
	float rx = Graphics.resolution_x;
	float ry = Graphics.resolution_y;
	if(font>0)
	{
		glBindTexture(GL_TEXTURE_2D, font);
		glBegin(GL_QUADS);
		float width = 16;
		float height = 32;
		float sz = text.size();
		for(int i = 0;i<sz;i++)
		{
			char currentc = text[i];
			if(currentc<255)
			{
				float dp1x = px + (i*width);
				float dp1y = py;
				float dp2x = dp1x + width;
				float dp2y = dp1y + height;
				/*dp1x/=rx;
				dp2x/=rx;
				dp1y/=ry;
				dp2y/=ry;*/
				dp1y=Graphics.resolution_y-dp1y;
				dp2y=Graphics.resolution_y-dp2y;
				glColor4f(1,1,1,1);
				glTexCoord2f((((int)currentc)*width)/4096.0f,1);
				glVertex3f(dp1x,dp1y,depth);
				glTexCoord2f((((int)currentc+1)*width)/4096.0f,1);
				glVertex3f(dp2x,dp1y,depth);
				glTexCoord2f((((int)currentc+1)*width)/4096.0f,0);
				glVertex3f(dp2x,dp2y,depth);
				glTexCoord2f((((int)currentc)*width)/4096.0f,0);
				glVertex3f(dp1x,dp2y,depth);
			}
		}
		glEnd();
		/*float rx = Graphics.resolution_x;
		float ry = Graphics.resolution_y;
		glBegin(GL_QUADS);
		glColor4f(1,1,1,1);
		float dpx[4] = 
		{
			(-0/rx),
			(640.0f/rx),
			(640.0f/rx),
			(-0/rx)
		};
		float dpy[4] = 
		{
			1.0f-((0)/ry),
			1.0f-((0)/ry),
			1.0f-(480.0f/ry),
			1.0f-(480.0f/ry)
		};
		glTexCoord2f(0,0);
		glVertex3f(dpx[0],dpy[0],depth);
		glTexCoord2f(1,0);
		glVertex3f(dpx[1],dpy[1],depth);
		glTexCoord2f(1,1);
		glVertex3f(dpx[2],dpy[2],depth);
		glTexCoord2f(0,1);
		glVertex3f(dpx[3],dpy[3],depth);
		glEnd();*/
	}
	glPopMatrix();
}

CGraphics::CGraphics()
{
	terminated=false;
	deltaTime=0;
	camera=nullptr;
	isInit=false;
	isWindow=false;
	resolution_x=-1;
	resolution_y=-1;
	cursorvisible=true;
}

void CGraphics::Init()
{
	glfwSwapInterval(1);
	glfwSetTime(0);
	isInit=true;
	Log.Log("Graphics system OK.",0);
}

void CGraphics::Window(bool fullscreen,float resx,float resy)
{
	resolution_x=resx;
	resolution_y=resy;
	glfwOpenWindow(resx,resy,16,16,16,16,16,16,(fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW));
	Log.Log("GLFW Window is open.",0);
	if(glfwGetWindowParam(GLFW_ACCELERATED)==GL_TRUE)
	{
		Log.Log("GLFW Window is accelerated.",1);
	}
	ShowCursor(false);
	isWindow=true;
	glfwSwapInterval(1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	//Blending requires ordering all objects on the screen, so it can go screw itself.
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER,0.5f);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_LIGHTING);
	Text.Init("Fonts\\VoxelFont.png");
	glClearColor(0,0.5f,0,1);
}

unsigned int CGraphics::LoadTexture(std::string filename,bool minmagmaps)
{
	if(filename!=""||!isWindow)
	{
		std::string fn = "Textures\\" + filename;
		GLuint tex = SOIL_load_OGL_texture(fn.c_str(),
			SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,
			SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);

		if(minmagmaps)
		{
			glBindTexture(GL_TEXTURE_2D, tex);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}

		return tex;
	}
	return 0;
}
unsigned int CGraphics::LoadTexture(std::string filename,bool minmagmaps,bool autotex)
{
	if(filename!=""||!isWindow)
	{
		std::string fn = "";
		if(autotex)
		{
			fn = "Textures\\" + filename;
		}
		else
		{
			fn = filename;
		}
		GLuint tex = SOIL_load_OGL_texture(fn.c_str(),
			SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,
			SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);

		if(minmagmaps)
		{
			glBindTexture(GL_TEXTURE_2D, tex);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}

		return tex;
	}
	return 0;
}
void CGraphics::FreeTexture(unsigned int texture)
{
	glDeleteTextures(1,&texture);
}

void CGraphics::ShowCursor(bool show)
{
	if(show==true)
	{
		glfwEnable(GLFW_MOUSE_CURSOR);
		cursorvisible=true;
	}
	else
	{
		glfwDisable(GLFW_MOUSE_CURSOR);
		cursorvisible=false;
	}
}
bool CGraphics::CursorVisible()
{
	return cursorvisible;
}

void CGraphics::Orthographic()
{
	glLoadIdentity();
	glOrtho(0,640,0,480,1.1f,-1.1f);
}

void CGraphics::Perspective()
{
	glLoadIdentity();
	if(camera!=nullptr)
	{
		gluPerspective(camera->fieldOfView,camera->aspectRatio,camera->nearZ,camera->farZ);
	}
	else
	{
		gluPerspective(60,4.0f/3.0f,0.1f,1.0f);
	}
}

void CGraphics::Begin()
{
	Perspective();
	if(camera)
	{
		if(camera->useQuat)
		{
			glRotatef(camera->rotation.getAngle()*(180.0f/PI)*2.0f,camera->rotation.getAxis().x(),camera->rotation.getAxis().y(),camera->rotation.getAxis().z());
		}
		else
		{
			glRotatef(camera->euler.z(),0,0,1);
			glRotatef(camera->euler.x(),1,0,0);
			glRotatef(camera->euler.y(),0,1,0);
		}
		glTranslatef(camera->position.x(),camera->position.y(),camera->position.z());
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CGraphics::End()
{
	glfwSwapBuffers();
	deltaTime=glfwGetTime();
	glfwSetTime(0);
}

void CGraphics::SetCamera(CCamera* newcam)
{
	camera=newcam;
}

void CGraphics::Terminate()
{
	if(!terminated)
	{
		glfwCloseWindow();
		Log.Log("GLFW Window has closed.",0);
		glfwTerminate();
		Log.Log("GLFW has terminated.",0);
		terminated=true;
	}
}
void CGraphics::EnableDepth()
{
	glEnable(GL_DEPTH_TEST);
}
void CGraphics::DisableDepth()
{
	glDisable(GL_DEPTH_TEST);
}

CGraphics Graphics;