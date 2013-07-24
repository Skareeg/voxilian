#include "Graphics.h"

void CCamera::Init(string newname)
{
	CEntity::Init(newname);
	SetType("CCamera");
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

CText::CText()
{
	font=0;
}
void CText::Init(string newfont)
{
	font=Graphics.LoadTexture(newfont,true);
}
void CText::DrawText(float px,float py,float depth,string text)
{
	//glPushMatrix();
	//Graphics.Orthographic();
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
			if(currentc>255)
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
	//Graphics.Perspective();
	//glPopMatrix();
}

CGraphics::CGraphics()
{
	resolution_x=-1;
	resolution_y=-1;
	camera=nullptr;
	isInit=false;
	isWindow=false;
}

void CGraphics::Init()
{
	glfwSwapInterval(1);
	cursorVisible=true;
	glfwSetTime(0);
	isInit=true;
}

void CGraphics::Window(bool fullscreen,float resx,float resy)
{
	resolution_x=resx;
	resolution_y=resy;
	if(fullscreen)
	{
		glfwOpenWindow(resx,resy,16,16,16,16,8,8,GLFW_FULLSCREEN);
	}
	else
	{
		glfwOpenWindow(resx,resy,16,16,16,16,8,8,GLFW_WINDOW);
	}
	Log.Log("GLFW Window is open.",0);
	if(glfwGetWindowParam(GLFW_ACCELERATED)==GL_TRUE)
	{
		Log.Log("GLFW Window is accelerated.",1);
	}
	ShowCursor(false);
	isWindow=true;
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER,0.4f);
	glShadeModel(GL_SMOOTH);
	Text.Init("Fonts\\VoxelFont.png");
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

void CGraphics::ShowCursor(bool show)
{
	if(show==true)
	{
		glfwEnable(GLFW_MOUSE_CURSOR);
		cursorVisible=true;
	}
	else
	{
		glfwDisable(GLFW_MOUSE_CURSOR);
		cursorVisible=false;
	}
}

void CGraphics::Orthographic()
{
	glOrtho(0,resolution_x,0,resolution_y,1.1f,-1.1f);
}

void CGraphics::Perspective()
{
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CGraphics::End()
{
	glfwSwapBuffers();
	deltaTime=glfwGetTime();
	glfwSetTime(0);
}

void CGraphics::Terminate()
{
	glfwCloseWindow();
	Log.Log("GLFW Window has closed.",0);
	glfwTerminate();
	Log.Log("GLFW has terminated.",0);
}

CGraphics Graphics;