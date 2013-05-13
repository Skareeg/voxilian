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
	distance_create=3;
	distance_render=2.5;
	distance_update=3.5f;
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
	}
	catch(exception ex)
	{
		cout<<"Render just went down.\n";
	}
}

VChunk::VChunk(VDimensia* d,VIndex nposition)
{
	try
	{
		state=0;
		dimensia=d;
		position=nposition;
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
						float hz = (float)(k+GetZ());
						float height = scaled_octave_noise_3d(1,1,0.05f,-16.0f,16.0f,hx,hz,0);
						if(j+GetY()==(int)height)
						{
							voxels[i][j][k].densities[0].vox_density=1.0f;
						}
					}
				}
			}
		//}
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
void Calculate()
{
	for(int i = 0;i<V_C_SIZEX;i++)
	{
		for(int j = 0;j<V_C_SIZEY;j++)
		{
			for(int k = 0;k<V_C_SIZEZ;k++)
			{
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
		VDensity standard = {1,0.0f,1,"VOX"};
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
				if(densities[i].vox_density>0.0f)
				{
					float mult = 0.0f;
					if(mult<V_C_SIZEX)mult=V_C_SIZEX;
					if(mult<V_C_SIZEY)mult=V_C_SIZEY;
					if(mult<V_C_SIZEZ)mult=V_C_SIZEZ;
					if(VMath::Distance(position.ToVector3(),*chunk->dimensia->manager->camera_pos)<mult*chunk->dimensia->manager->distance_render)
					{
						if(densities[i].vox_type==1)
						{
							Draw::Cube(position.x,position.y,position.z);
						}
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