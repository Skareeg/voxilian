#include "VOX.h"
#include <Windows.h>
#include <cstdio>

void VIndex::FromVector3(Vector3 v)
{
	x=(int)floorf(v.x);
	y=(int)floorf(v.y);
	z=(int)floorf(v.z);
}
Vector3 VIndex::ToVector3()
{
	Vector3 r;
	r.x=x;
	r.y=y;
	r.z=z;
	return r;
}
bool VIndex::Compare(VIndex v)
{
	if(x==v.x)
	{
		if(y==v.y)
		{
			if(z==v.z)
			{
				return true;
			}
		}
	}
	return false;
}
VIndex VIndex::operator+(VIndex v)
{
	VIndex r;
	r.x=x+v.x;
	r.y=y+v.y;
	r.z=z+v.z;
	return r;
}
VIndex VIndex::operator-(VIndex v)
{
	VIndex r;
	r.x=x-v.x;
	r.y=y-v.y;
	r.z=z-v.z;
	return r;
}
VIndex VINDEX(int i,int j,int k)
{
	VIndex v;
	v.x=i;
	v.y=j;
	v.z=k;
	return v;
}

void VManager::Init(Vector3* campos)
{
	_wmkdir(L"Dimensias");
	camera_pos=campos;
	distance_create=1;
	distance_render=1;
	distance_update=10;
	dimensia=new VDimensia(this,"Main");
}
void VManager::Render()
{
	dimensia->Render();
	if(glS.GetKey('F')==GLFW_PRESS)
	{
		glS.ShowCursor(true);
	}
	if(glS.GetKey('G')==GLFW_PRESS)
	{
		glS.ShowCursor(false);
	}
}

void InitChunk(VChunk* ch)
{
	try
	{
		ch->Init();
	}
	catch(exception ex)
	{
		cout<<ex.what();
	}
}
void AttemptCreate(VDimensia* v,VIndex pos,VIndex cam_index,Vector3 cam_vec,float dist)
{
	if(VMath::Distance(cam_vec+pos.ToVector3(),cam_vec)<dist)
	{
		VIndex cpos = VINDEX(pos.x+cam_index.x,pos.y+cam_index.y,pos.z+cam_index.z);
		bool good = true;
		try
		{
			for(int l = 0;l<v->chunks.size();l++)
			{
				if(cpos.Compare(v->chunks.at(l)->position)==true)
				{
					good=false;
				}
			}
			if(good==true)
			{
				VChunk* nc = new VChunk(v,cpos);
				InitChunk(nc);
				v->chunks.push_back(nc);
				try
				{
					nc->NCalculate();
					for(int i = -1;i<=1;i++)
					{
						for(int j = -1;j<=1;j++)
						{
							for(int k = -1;k<=1;k++)
							{
								if(nc->ne[i+1][j+1][k+1]!=nullptr)
								{
									nc->ne[i+1][j+1][k+1]->ne[-i+1][-j+1][-k+1]=nc;
								}
							}
						}
					}
					nc->VCalculate();
				}
				catch(exception ex)
				{
					LOGW1("EXCEPTION: ATTEMPTCREATE(v,pos,vind,vec,float)\n.");
				}
			}
		}
		catch(exception ex)
		{
			cout<<"CHUNK CREATE IGNORED! HAHAHAHAHA! >:)\n"<<ex.what()<<"\n";
		}
	}
}
void ChunkCreateByIndexement(VDimensia* v)
{
	try
	{
		Vector3 cam_vec = *(v->manager->camera_pos);
		VIndex cam_index;
		cam_vec.x*=V_C_SCALEX;
		cam_vec.y*=V_C_SCALEY;
		cam_vec.z*=V_C_SCALEZ;
		cam_vec.x-=0.5f;
		cam_vec.y-=0.5f;
		cam_vec.z-=0.5f;
		cam_index.FromVector3(cam_vec);
		float dist = v->manager->distance_create;
		float d2 = dist / 2.0f;
		AttemptCreate(v,VINDEX(0,0,0),cam_index,cam_vec,dist);
		for(int i = 1;i<=d2;i++)
		{
			for(int j = 0;j<=i;j++)
			{
				for(int k = 0;k<=i;k++)
				{
					AttemptCreate(v,VINDEX(j,i,k),cam_index,cam_vec,dist);
					AttemptCreate(v,VINDEX(j,-i,k),cam_index,cam_vec,dist);
					AttemptCreate(v,VINDEX(i,j,k),cam_index,cam_vec,dist);
					AttemptCreate(v,VINDEX(-i,j,k),cam_index,cam_vec,dist);
					AttemptCreate(v,VINDEX(j,k,i),cam_index,cam_vec,dist);
					AttemptCreate(v,VINDEX(j,k,-i),cam_index,cam_vec,dist);
				}
			}
		}
	}
	catch(exception ex)
	{
		cout<<"The Chunk creation code just failed.\n";
	}
}
void ChunkDestroy(VDimensia* v)
{
	try
	{
		Vector3 cam_vec = *(v->manager->camera_pos);
		cam_vec.x*=V_C_SCALEX;
		cam_vec.y*=V_C_SCALEY;
		cam_vec.z*=V_C_SCALEZ;
		cam_vec.x-=0.5f;
		cam_vec.y-=0.5f;
		cam_vec.z-=0.5f;
		float dist = v->manager->distance_update;
		float d2 = dist / 2.0f;
		for(int i = 0;i<v->chunks.size();i++)
		{
			if(VMath::Distance(v->chunks.at(i)->position.ToVector3(),cam_vec)>dist)
			{
				VChunk* vc = v->chunks.at(i);
				v->chunks.erase(v->chunks.begin()+i);
				vc->Destroy();
				delete vc;
			}
		}
	}
	catch(exception ex)
	{
		cout<<"ChunkDestroy decided not to work.\n";
	}
}

VDimensia::VDimensia(VManager* m,string nm)
{
	string dn = "Dimensias\\"+nm;
	wstring wdn  = wstring(dn.begin(),dn.end());
	CreateDirectory(wdn.c_str(),NULL);
	name=nm;
	manager=m;
	isolevel=0.5f;
}
void VDimensia::Render()
{
	try
	{
		if(glfwWaitThread(thread_chunk_manage,GLFW_NOWAIT)==GL_TRUE)
		{
			thread_chunk_manage=glfwCreateThread((GLFWthreadfun)ChunkCreateByIndexement,this);
		}
		if(glfwWaitThread(thread_chunk_destroy,GLFW_NOWAIT)==GL_TRUE)
		{
			thread_chunk_destroy=glfwCreateThread((GLFWthreadfun)ChunkDestroy,this);
		}
		int sz = chunks.size();
		for(int i = 0;i<sz;i++)
		{
			try
			{
				chunks.at(i)->Render();
			}
			catch(exception ex)
			{
				cout<<"RENDER FAIL COUNTER! >:)\n";
			}
		}
		if(glS.GetKey('R')==true)
		{
			VoxelDestroySphere(*manager->camera_pos,2.0f,0.1f,0.1f);
		}
	}
	catch(exception ex)
	{
		cout<<"Render just went down.\n";
	}
}
VChunk* VDimensia::GetChunk(VIndex pos)
{
	try
	{
		for(int i = 0;i<chunks.size();i++)
		{
			if(pos.Compare(chunks.at(i)->position)==true)
			{
				return chunks.at(i);
			}
		}
	}
	catch(exception ex)
	{
		LOGW1("VDimensia::GetChunk(xyz) failure detected.\n");
	}
	return nullptr;
}
VVoxel* VDimensia::GetVoxel(VIndex wpos)
{
	try
	{
		VIndex cpos = VINDEX(
			floorf((float)wpos.x/V_C_SIZEX),
			floorf((float)wpos.y/V_C_SIZEY),
			floorf((float)wpos.z/V_C_SIZEZ));
		VIndex vpos = VINDEX(
			wpos.x-(cpos.x*V_C_SIZEX),
			wpos.y-(cpos.y*V_C_SIZEY),
			wpos.z-(cpos.z*V_C_SIZEZ));
		for(int b = 0;b<chunks.size();b++)
		{
			if(cpos.Compare(chunks.at(b)->position)==true)
			{
				return &chunks.at(b)->voxels[vpos.x][vpos.y][vpos.z];
			}
		}
	}
	catch(exception ex)
	{
	}
	return nullptr;
}
struct DVDS
{
	VDimensia* d;
	Vector3 pos;
	float radius;
	float impactsoft;
	float impactsolid;
};
void DimensiaVoxelDestroySphere(DVDS* dvds)
{
	try
	{
		if(dvds->impactsoft<1.0f)
		{
			dvds->impactsoft=1.0f;
		}
		if(dvds->impactsolid<0.0f)
		{
			dvds->impactsolid=0.0f;
		}
		Vector3 p = dvds->pos;
		float r = dvds->radius;
		for(int i = 0;i<dvds->d->chunks.size();i++)
		{
			VChunk* c = dvds->d->chunks.at(i);
			Vector3 cp = c->GetPos().ToVector3();
			float dist = VMath::Distance(p,cp);
			float md = V_C_SIZEX;
			if(md<V_C_SIZEY)
			{
				md=V_C_SIZEY;
			}
			if(md<V_C_SIZEZ)
			{
				md=V_C_SIZEZ;
			}
			float fd = dist - md;
			if(fd<r)
			{
				for(int j = 0;j<V_C_SIZEX;j++)
				{
					for(int k = 0;k<V_C_SIZEY;k++)
					{
						for(int l = 0;l<V_C_SIZEZ;l++)
						{
							Vector3 vp = c->voxels[j][k][l].position.ToVector3()+VMath::Vector(0.5f,0.5f,0.5f);
							float vd = VMath::Distance(p,vp);
							if(vd<r)
							{
								for(int m = 0;m<c->voxels[j][k][l].densities.size();m++)
								{
									c->voxels[j][k][l].densities.at(m).vox_density/=(dvds->impactsoft+1.0f);
									c->voxels[j][k][l].densities.at(m).vox_density-=dvds->impactsolid;
								}
								for(int f = 0;f<3;f++)
								for(int g = 0;g<3;g++)
								for(int h = 0;h<3;h++)
									if(c->voxels[j][k][l].ne[f][g][h]!=nullptr)
									{
										c->voxels[j][k][l].ne[f][g][h]->VCalculate();
									}
							}
						}
					}
				}
			}
		}
	}
	catch(exception ex)
	{
		LOGW1("VoxelDestroySphere has failed.\n");
	}
	delete dvds;
}
void VDimensia::VoxelDestroySphere(Vector3 pos,float radius,float soft,float hard)
{
	DVDS* d = new DVDS();
	d->d=this;
	d->pos=pos;
	d->radius=radius;
	d->impactsoft=soft;
	d->impactsolid=hard;
	glfwCreateThread((GLFWthreadfun)DimensiaVoxelDestroySphere,d);
}

void ChunkBoxLines(VChunk* v)
{
	try
	{
		v->b_lines.push_back(
			VMath::Vector(0,0,0));
		v->b_lines.push_back(
			VMath::Vector(1,0,0));
		v->b_lines.push_back(
			VMath::Vector(0,0,0));
		v->b_lines.push_back(
			VMath::Vector(0,1,0));
		v->b_lines.push_back(
			VMath::Vector(0,0,0));
		v->b_lines.push_back(
			VMath::Vector(0,0,1));
	}
	catch(exception ex)
	{
	}
}
void ChunkNeLines(VChunk* v)
{
	try
	{
		if(v!=nullptr)
		{
			v->d_lines.clear();
			for(int i = -1;i<=1;i++)
			{
				for(int j = -1;j<=1;j++)
				{
					for(int k = -1;k<=1;k++)
					{
						if((v->ne[i+1][j+1][k+1])!=nullptr)
						{
							v->d_lines.push_back(
								VMath::Vector(0.5f,0.5f,0.5f));
							v->d_lines.push_back(
								VMath::Vector(0.5f+((float)i/4.0f),0.5f+((float)j/4.0f),0.5f+((float)k/4.0f)));
						}
					}
				}
			}
		}
	}
	catch(exception ex)
	{
	}
}
VChunk::VChunk(VDimensia* d,VIndex nposition)
{
	try
	{
		state=0;
		dimensia=d;
		position=nposition;
		for(int i = 0;i<3;i++)
		{
			for(int j = 0;j<3;j++)
			{
				for(int k = 0;k<3;k++)
				{
					ne[i][j][k]=nullptr;
				}
			}
		}
		render=false;
	}
	catch(exception ex)
	{
		cout<<"VChunk failure with an attempt at ";nposition.ToVector3().CoutShow();cout<<"\n";
	}
}
void VChunk::Init()
{
	try
	{
		ChunkBoxLines(this);
		char x[8];
		char y[8];
		char z[8];
		itoa(position.x,x,10);
		itoa(position.y,y,10);
		itoa(position.z,z,10);
		_wmkdir(L"Dimensias");
		string fname = "Dimensias\\"+dimensia->name+"\\"+
			x+"_"+y+"_"+z+".bin";
		const char* fnamec = fname.c_str();
		//regionfile.open(fnamec,ios_base::in|ios_base::out|ios_base::binary);
		//if(regionfile.eof()==true)
		//{
			for(int i = 0;i<V_C_SIZEX;i++)
			{
				for(int j = 0;j<V_C_SIZEY;j++)
				{
					for(int k = 0;k<V_C_SIZEZ;k++)
					{
						voxels[i][j][k].Init(this,VINDEX(i,j,k));
						float hx = (float)(i+GetX());
						float hy = (float)(j+GetY());
						float hz = (float)(k+GetZ());
						float min = -16.0f;
						float max = 16.0f;
						float precision = max-min;
						float height = scaled_octave_noise_3d(1.0f,1.0f,0.05f,min,max,hx,hz,0.0f);
						float basey = hy-min;
						float baseh = abs(height-min);
						if(basey<0.0f)
						{
							voxels[i][j][k].densities.at(0).vox_density=1.0f;
						}
						if(basey>=0.0f&&basey<=baseh)
						{
							voxels[i][j][k].densities.at(0).vox_density=abs(1.0f-(basey/baseh));
						}
						if(baseh>baseh)
						{
							voxels[i][j][k].densities.at(0).vox_density=0.0f;
						}
					}
				}
			}
		/*
		}
		*/
		state=1;
	}
	catch(exception ex)
	{
		cout<<"Hold up... Chunk init just failed?\n";
	}
}
void ChunkUpdate(VChunk* ch)
{
	try
	{
	}
	catch(exception ex)
	{
		cout<<ex.what();
	}
}
void VChunk::Update()
{
	try
	{
		if(state==1)
		{
		}
	}
	catch(exception ex)
	{
		cout<<ex.what();
	}
}
void VChunk::Render()
{
	try
	{
		//Debug Line Codes. Deprecated.
		/*glPushMatrix();
		glScalef(V_C_SIZEX,V_C_SIZEY,V_C_SIZEZ);
		glTranslatef(position.x,position.y,position.z);
		glBegin(GL_LINES);
		glColor3f(0.8f,0.8f,0.8f);
		try
		{
			for(int i = 0;i<d_lines.size();i++)
			{
				glVertex3f(d_lines.at(i).x,d_lines.at(i).y,d_lines.at(i).z);
			}
			for(int i = 0;i<b_lines.size();i++)
			{
				glVertex3f(b_lines.at(i).x,b_lines.at(i).y,b_lines.at(i).z);
			}
		}
		catch(exception ex)
		{
		}
		glEnd();
		glPopMatrix();*/
		if(state==1)
		{
			Vector3 cam_vec = *(dimensia->manager->camera_pos);
			cam_vec.x*=V_C_SCALEX;
			cam_vec.y*=V_C_SCALEY;
			cam_vec.z*=V_C_SCALEZ;
			cam_vec.x-=0.5f;
			cam_vec.y-=0.5f;
			cam_vec.z-=0.5f;
			if(VMath::Distance(position.ToVector3(),cam_vec)<dimensia->manager->distance_render)
			{
				for(int i = 0;i<V_C_SIZEX;i++)
				{
					for(int j = 0;j<V_C_SIZEY;j++)
					{
						for(int k = 0;k<V_C_SIZEZ;k++)
						{
							voxels[i][j][k].Render();
						}
					}
				}
			}
		}
	}
	catch(exception ex)
	{
		cout<<"Chunk::Render failed just now.\n";
	}
}
void VChunk::Destroy()
{
	try
	{
		/*for(int i = 0;i<V_C_SIZEX;i++)
		{
			for(int j = 0;j<V_C_SIZEY;j++)
			{
				for(int k = 0;k<V_C_SIZEZ;k++)
				{
					voxels[i][j][k].Save(&regionfile);
				}
			}
		}*/
		for(int i = -1;i<=1;i++)
		{
			for(int j = -1;j<=1;j++)
			{
				for(int k = -1;k<=1;k++)
				{
					if((ne[i+1][j+1][k+1])!=nullptr)
					{
						ne[i+1][j+1][k+1]->ne[1-i][1-j][1-k]=nullptr;
						ChunkNeLines(ne[i+1][j+1][k+1]);
					}
				}
			}
		}
	}
	catch(exception ex)
	{
		cout<<"File writing issue!\n";
	}
}
VIndex VChunk::GetPos()
{
	try
	{
	VIndex pos = position;
	pos.x*=V_C_SIZEX;
	pos.y*=V_C_SIZEY;
	pos.z*=V_C_SIZEZ;
	return pos;
	}
	catch(exception ex)
	{
		cout<<ex.what();
	}
}
int VChunk::GetX()
{
	try
	{
	return position.x*V_C_SIZEX;
	}
	catch(exception ex)
	{
		cout<<ex.what();
	}
}
int VChunk::GetY()
{
	try
	{
	return position.y*V_C_SIZEY;
	}
	catch(exception ex)
	{
		cout<<ex.what();
	}
}
int VChunk::GetZ()
{
	try
	{
	return position.z*V_C_SIZEZ;
	}
	catch(exception ex)
	{
		cout<<ex.what();
	}
}
void VChunk::NCalculate()
{
	try
	{
		for(int i = -1;i<=1;i++)
		{
			for(int j = -1;j<=1;j++)
			{
				for(int k = -1;k<=1;k++)
				{
					ne[i+1][j+1][k+1]=dimensia->GetChunk(position+VINDEX(i,j,k));
					ChunkNeLines(ne[i+1][j+1][k+1]);
				}
			}
		}
		ChunkNeLines(this);
		for(int i = 0;i<V_C_SIZEX;i++)
		{
			for(int j = 0;j<V_C_SIZEY;j++)
			{
				for(int k = 0;k<V_C_SIZEZ;k++)
				{
					voxels[i][j][k].NCalculate();
				}
			}
		}
	}
	catch(exception ex)
	{
		LOGW1(ex.what());LOGW1("\n");
	}
}
void VChunk::VCalculate()
{
	for(int i = 0;i<V_C_SIZEX;i++)
	{
		for(int j = 0;j<V_C_SIZEY;j++)
		{
			for(int k = 0;k<V_C_SIZEZ;k++)
			{
				voxels[i][j][k].VCalculate();
			}
		}
	}
}

VVoxel::VVoxel()
{
	for(int i = 0;i<3;i++)
	{
		for(int j = 0;j<3;j++)
		{
			for(int k = 0;k<3;k++)
			{
				ne[i][j][k]=nullptr;
			}
		}
	}
}
void VVoxel::Init(VChunk* c,VIndex p)
{
	try
	{
		chunk=c;
		position=p+c->GetPos();
		index=p;
		VDensity standard;
		standard.name="VOX";
		standard.vox_density=0.0f;
		standard.vox_id=0;
		standard.vox_type=V_TYPE_MESH;
		densities.push_back(standard);
	}
	catch(exception ex)
	{
		cout<<"Hey... a voxel failed. Cool.\n";
	}
}
void VVoxel::Render()
{
	try
	{
		for(int i = 0;i<densities.size();i++)
		{
			try
			{
				float mult = 0.0f;
				if(mult<V_C_SIZEX)mult=V_C_SIZEX;
				if(mult<V_C_SIZEY)mult=V_C_SIZEY;
				if(mult<V_C_SIZEZ)mult=V_C_SIZEZ;
				if(VMath::Distance(position.ToVector3(),*chunk->dimensia->manager->camera_pos)<mult*chunk->dimensia->manager->distance_render)
				{
					if(densities.at(i).vox_type==V_TYPE_CUBE)
					{
						if(densities.at(i).vox_density>0.0f)
						{
							Draw::CubeSide(position.x,position.y,position.z,
								drawsides[DRAW_CUBE_DOWN],
								drawsides[DRAW_CUBE_UP],
								drawsides[DRAW_CUBE_LEFT],
								drawsides[DRAW_CUBE_RIGHT],
								drawsides[DRAW_CUBE_BACKWARD],
								drawsides[DRAW_CUBE_FORWARD]);
						}
					}
					if(densities.at(i).vox_type==V_TYPE_MESH)
					{
						glBegin(GL_TRIANGLES);
						try
						{
							for(int j = 0;j<densities.size();j++)
							{
								for(int k = 0;k<densities.at(j).vmesh.size();k++)
								{
									glColor3f(1,0,0);
									glVertex3f(densities.at(j).vmesh.at(k).p[0].x,densities.at(j).vmesh.at(k).p[0].y,densities.at(j).vmesh.at(k).p[0].z);
									glColor3f(0,1,0);
									glVertex3f(densities.at(j).vmesh.at(k).p[1].x,densities.at(j).vmesh.at(k).p[1].y,densities.at(j).vmesh.at(k).p[1].z);
									glColor3f(0,0,1);
									glVertex3f(densities.at(j).vmesh.at(k).p[2].x,densities.at(j).vmesh.at(k).p[2].y,densities.at(j).vmesh.at(k).p[2].z);
								}
							}
						}
						catch(exception ex)
						{
							cout<<"Problem!\n";
						}
						glEnd();
					}
				}
			}
			catch(exception ex)
			{
				cout<<"NODRAW VOXEL DUE TO DENSITY LOSS! (or error of somekind)\n";
			}
		}
	}
	catch(exception ex)
	{
		cout<<"A voxel does not like his density list.\n";
	}
}
void VVoxel::Save(fstream* f)
{
	(*f)<<densities.size()<<':';
	for(int i = 0;i<densities.size();i++)
	{
		(*f)<<sizeof(densities[i]);
		f->write((char*)&densities[i],sizeof(densities[i]));
	}
}
void VVoxel::Load(fstream* f)
{
	int sized = 0;
	(*f)>>sized;
	densities.resize(sized);
	for(int i = 0;i<sized;i++)
	{
		int denssize = 0;
		(*f)>>denssize;
		f->get((char*)&densities[i],denssize);
	}
}
int CheckVI(int i,int m)
{
	if(i<0)
	{
		return m-1;
	}
	if(i>=m)
	{
		return 0;
	}
	return i;
}
void VVoxel::NCalculate()
{
	try
	{
		for(int a = -1;a<=1;a++)
		{
			for(int s = -1;s<=1;s++)
			{
				for(int d = -1;d<=1;d++)
				{
					int sx = index.x+a;
					int sy = index.y+s;
					int sz = index.z+d;
					int aa = a+1;
					int ss = s+1;
					int dd = d+1;
					int z = CheckVI(sx,V_C_SIZEX);
					int x = CheckVI(sy,V_C_SIZEY);
					int c = CheckVI(sz,V_C_SIZEZ);
					int q = 1;
					int w = 1;
					int e = 1;
					if(sx==-1)
					{
						q=0;
						sx=19;
					}
					if(sx==V_C_SIZEX)
					{
						q=2;
						sx=0;
					}
					if(sy==-1)
					{
						w=0;
						sy=19;
					}
					if(sy==V_C_SIZEY)
					{
						w=2;
						sy=0;
					}
					if(sz==-1)
					{
						e=0;
						sz=19;
					}
					if(sz==V_C_SIZEZ)
					{
						e=2;
						sz=0;
					}
					ne[aa][ss][dd]=nullptr;
					if(chunk->ne[q][w][e]!=nullptr)
					{
						//aa = a+1
						//ss = s+1
						//dd = d+1
						//q,w,e = chunk neighbor numbers. 0,1,2.
						ne[aa][ss][dd]=&chunk->ne[q][w][e]->voxels[sx][sy][sz];
						if(ne[aa][ss][dd]!=nullptr)
						{
							chunk->ne[q][w][e]->voxels[sx][sy][sz].ne[2-aa][2-ss][2-dd]=this;
							try
							{
								chunk->ne[q][w][e]->voxels[sx][sy][sz].VCalculate();
							}
							catch(exception ex)
							{
								cout<<ex.what()<<"\n";
							}
						}
					}
				}
			}
		}
	}
	catch(exception ex)
	{
		LOGW1(ex.what());LOGW1("\n");
		cout<<"FAIL";
	}
}
void VVoxel::VCalculate()
{
	try
	{
		for(int i = 0;i<6;i++)
		{
			drawsides[i]=0;
		}
		if(ne[0][1][1]!=nullptr)
		{
			for(int i = 0;i<ne[0][1][1]->densities.size();i++)
			{
				if(ne[0][1][1]->densities.at(i).vox_density==0)
				{
					drawsides[DRAW_CUBE_LEFT]=1;
				}
			}
		}
		else
		{
			//drawsides[DRAW_CUBE_LEFT]=1;
		}
		if(ne[2][1][1]!=nullptr)
		{
			for(int i = 0;i<ne[2][1][1]->densities.size();i++)
			{
				if(ne[2][1][1]->densities.at(i).vox_density==0)
				{
					drawsides[DRAW_CUBE_RIGHT]=1;
				}
			}
		}
		else
		{
			//drawsides[DRAW_CUBE_RIGHT]=1;
		}
		if(ne[1][0][1]!=nullptr)
		{
			for(int i = 0;i<ne[1][0][1]->densities.size();i++)
			{
				if(ne[1][0][1]->densities.at(i).vox_density==0)
				{
					drawsides[DRAW_CUBE_DOWN]=1;
				}
			}
		}
		else
		{
			//drawsides[DRAW_CUBE_DOWN]=1;
		}
		if(ne[1][2][1]!=nullptr)
		{
			for(int i = 0;i<ne[1][2][1]->densities.size();i++)
			{
				if(ne[1][2][1]->densities.at(i).vox_density==0)
				{
					drawsides[DRAW_CUBE_UP]=1;
				}
			}
		}
		else
		{
			//drawsides[DRAW_CUBE_UP]=1;
		}
		if(ne[1][1][0]!=nullptr)
		{
			for(int i = 0;i<ne[1][1][0]->densities.size();i++)
			{
				if(ne[1][1][0]->densities.at(i).vox_density==0)
				{
					drawsides[DRAW_CUBE_BACKWARD]=1;
				}
			}
		}
		else
		{
			//drawsides[DRAW_CUBE_BACKWARD]=1;
		}
		if(ne[1][1][2]!=nullptr)
		{
			for(int i = 0;i<ne[1][1][2]->densities.size();i++)
			{
				if(ne[1][1][2]->densities.at(i).vox_density==0)
				{
					drawsides[DRAW_CUBE_FORWARD]=1;
				}
			}
		}
		else
		{
			//drawsides[DRAW_CUBE_FORWARD]=1;
		}
		int nt = 0;
		for(int i = 0;i<densities.size();i++)
		{
			densities.at(i).vmesh.clear();
			densities.at(i).vcell.p[0]=(position+VINDEX(0,0,0)).ToVector3();
			densities.at(i).vcell.p[1]=(position+VINDEX(1,0,0)).ToVector3();
			densities.at(i).vcell.p[2]=(position+VINDEX(1,0,1)).ToVector3();
			densities.at(i).vcell.p[3]=(position+VINDEX(0,0,1)).ToVector3();
			densities.at(i).vcell.p[4]=(position+VINDEX(0,1,0)).ToVector3();
			densities.at(i).vcell.p[5]=(position+VINDEX(1,1,0)).ToVector3();
			densities.at(i).vcell.p[6]=(position+VINDEX(1,1,1)).ToVector3();
			densities.at(i).vcell.p[7]=(position+VINDEX(0,1,1)).ToVector3();
			if(ne[1][1][1]!=nullptr)
			{
				densities.at(i).vcell.val[0]=ne[1][1][1]->densities.at(i).vox_density;
			}
			else
			{
				densities.at(i).vcell.val[0]=0.0f;
			}
			if(ne[2][1][1]!=nullptr)
			{
				densities.at(i).vcell.val[1]=ne[2][1][1]->densities.at(i).vox_density;
			}
			else
			{
				densities.at(i).vcell.val[1]=0.0f;
			}
			if(ne[2][1][2]!=nullptr)
			{
				densities.at(i).vcell.val[2]=ne[2][1][2]->densities.at(i).vox_density;
			}
			else
			{
				densities.at(i).vcell.val[2]=0.0f;
			}
			if(ne[1][1][2]!=nullptr)
			{
				densities.at(i).vcell.val[3]=ne[1][1][2]->densities.at(i).vox_density;
			}
			else
			{
				densities.at(i).vcell.val[3]=0.0f;
			}
			if(ne[1][2][1]!=nullptr)
			{
				densities.at(i).vcell.val[4]=ne[1][2][1]->densities.at(i).vox_density;
			}
			else
			{
				densities.at(i).vcell.val[4]=0.0f;
			}
			if(ne[2][2][1]!=nullptr)
			{
				densities.at(i).vcell.val[5]=ne[2][2][1]->densities.at(i).vox_density;
			}
			else
			{
				densities.at(i).vcell.val[5]=0.0f;
			}
			if(ne[2][2][2]!=nullptr)
			{
				densities.at(i).vcell.val[6]=ne[2][2][2]->densities.at(i).vox_density;
			}
			else
			{
				densities.at(i).vcell.val[6]=0.0f;
			}
			if(ne[1][2][2]!=nullptr)
			{
				densities.at(i).vcell.val[7]=ne[1][2][2]->densities.at(i).vox_density;
			}
			else
			{
				densities.at(i).vcell.val[7]=0.0f;
			}
			nt+=VoxelFunc::Polygonise(densities.at(i).vcell,chunk->dimensia->isolevel,&densities.at(i).vmesh);
		}
	}
	catch(exception ex)
	{
		cout<<"VCalcFailure\n";
	}
}