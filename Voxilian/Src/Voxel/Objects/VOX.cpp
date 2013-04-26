#include "VOX.h"
#include <noise\noise.h>

using namespace Spacial;

bool VIndex::Compare(VIndex* v)
{
	if(x==v->x)
	{
		if(y==v->y)
		{
			if(z==v->z)
			{
				return true;
			}
		}
	}
	return false;
}
VIndex::VIndex()
{
	x=0;y=0;z=0;
}
VIndex::VIndex(Vector3 v)
{
	x=v.x;y=v.y;z=v.z;
}
VIndex::VIndex(VIndex* v)
{
	x=v->x;y=v->y;z=v->z;
}
VIndex::VIndex(int i,int j,int k)
{
	x=i;y=j;z=k;
}
static VIndex* VINDEX(int i,int j,int k)
{
	VIndex* v = new VIndex(i,j,k);
	return v;
}

void CreateChunkUnderDecision(Manager* m,int i,int j,int k)
{
	//Change cam to index position.
	//Test and create chunks.
	Vector3 cipos;
	cipos.x=floor(m->cpos->x)/VOX_VOXELSIZE_X;
	cipos.y=floor(m->cpos->y)/VOX_VOXELSIZE_Y;
	cipos.z=floor(m->cpos->z)/VOX_VOXELSIZE_Z;
	Vector3 cvpos;
	cvpos=(cipos+VMath::Vector(i,j,k));
	if(VMath::Distance(
		(*(m->cpos))*VMath::Vector(1/(float)VOX_VOXELSIZE_X,1/(float)VOX_VOXELSIZE_Y,1/(float)VOX_VOXELSIZE_Z)
		,(cvpos+VMath::Vector(0.5f,0.5f,0.5f)))<m->mindist)
	{
		VIndex* crpos = new VIndex(cipos.x+i,cipos.y+j,cipos.z+k);
		bool good = true;
		for(int l = 0;l<m->registry.size();l++)
		{
			if(m->registry[l]->Compare(crpos)==true)
			{
				good=false;
			}
		}
		if(good==true)
		{
			Chunk* c = new Chunk(m,crpos);
			c->Init();
			m->create.push_back(c);
			m->registry.push_back(crpos);
			cout<<"Voxel at "<<crpos->x<<":"<<crpos->y<<":"<<crpos->z<<" created successfully.\n";
		}
		else
		{
			delete crpos;
		}
	}
}
void ChunkInit(Chunk* c)
{
	/*for(int i = -1;i<=1;i++)
	{
		for(int j = -1;j<=1;j++)
		{
			for(int k = -1;k<=1;k++)
			{
				c->neighbors[i][j][k]=c->manager->GetChunk(VINDEX(i,j,k));
				if(c->neighbors[i][j][k]!=nullptr)
				{
					c->neiexists[i][j][k]=false;
				}
				else
				{
					c->neiexists[i][j][k]=true;
				}
			}
		}
	}*/
	c->voxels=new Voxel**[VOX_VOXELSIZE_X];
	for(int i = 0;i<VOX_VOXELSIZE_X;i++)
	{
		c->voxels[i] = new Voxel*[VOX_VOXELSIZE_Y];
		for(int j = 0;j<VOX_VOXELSIZE_Y;j++)
		{
			c->voxels[i][j] = new Voxel[VOX_VOXELSIZE_Z];
			for(int k = 0;k<VOX_VOXELSIZE_Z;k++)
			{
				VIndex vind;
				vind.x=i;
				vind.y=j;
				vind.z=k;
				c->voxels[i][j][k].Init(c,vind);
			}
		}
	}
	c->state=CHUNKSTATE::READY;
}
void ChunkDestroy(Chunk* c)
{
	for(int i = VOX_VOXELSIZE_X-1;i>=0;i--)
	{
		for(int j = VOX_VOXELSIZE_Y-1;j>=0;j--)
		{
			delete [] c->voxels[i][j];
		}
		delete [] c->voxels[i];
	}
	delete [] c->voxels;
}

void WorldGen::Init()
{
	time_t* t = new time_t;
	time(t);
}
float WorldGen::GetLocation(Vector3 vpos)
{
	float d = 0;
	const float x = vpos.x/200.0f;
	const float y = vpos.y*0;
	const float z = vpos.z/200.0f;
	float height = 0;
	height = scaled_octave_noise_3d(2,2,1.0f,-64.0f,0.0f,x,y,z);
	if(vpos.y==floor(height)&&(int)vpos.x%2==0&&(int)vpos.z%2==0)
	{
		d=1.0f;
	}
	else
	{
		d=0.0f;
	}
	return d;
}

void Manager::Init(Vector3* cm)
{
	cpos=cm;
	mindist=4.0f;
	maxdist=7.0f;
	renderthread=glfwGetThreadID();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}
void ManagerUpdate(Manager* m)
{
	CreateChunkUnderDecision(m,0,0,0);
	for(int i = 1;i<=m->mindist;i++)
	{
		for(int j = 1;j<=m->mindist;j++)
		{
			for(int k = 1;k<=m->mindist;k++)
			{
				CreateChunkUnderDecision(m,i,j,k);
				CreateChunkUnderDecision(m,i,j,-k);
				CreateChunkUnderDecision(m,-i,j,k);
				CreateChunkUnderDecision(m,-i,j,-k);
				CreateChunkUnderDecision(m,i,-j,k);
				CreateChunkUnderDecision(m,i,-j,-k);
				CreateChunkUnderDecision(m,-i,-j,k);
				CreateChunkUnderDecision(m,-i,-j,-k);
			}
		}
	}
	for(int i = 0;i<m->registry.size();i++)
	{
		//Change cam to index position.
		//Test and destroy chunks.
		Vector3 cipos;
		cipos.x=floor(m->cpos->x)/VOX_VOXELSIZE_X;
		cipos.y=floor(m->cpos->y)/VOX_VOXELSIZE_Y;
		cipos.z=floor(m->cpos->z)/VOX_VOXELSIZE_Z;
		Vector3 v = VMath::Vector(m->registry[i]->x,m->registry[i]->y,m->registry[i]->z);
		if(VMath::Distance(cipos,v)>m->maxdist)
		{
			m->destroy.push_back(&m->chunks[i].vindex);
			//m->registry.erase(m->registry.begin()+i);
			//m->chunks.erase(m->chunks.begin()+i);//
			cout<<"Voxel at "<<v.x<<":"<<v.y<<":"<<v.z<<" place to remove successfully.\n";
		}
	}
}
void Manager::Update()
{
	if(glfwWaitThread(mainthread,GLFW_NOWAIT)==GL_TRUE)
	{
		int sz = destroy.size();
		for(int i = 0;i<sz;i++)
		{
			DestroyChunk(destroy[i]);
		}
		destroy.clear();
		sz = create.size();
		for(int i = 0;i<sz;i++)
		{
			chunks.push_back(*create[i]);
		}
		create.clear();
		glfwDestroyThread(mainthread);
		mainthread = glfwCreateThread((GLFWthreadfun)ManagerUpdate,this);
	}
}
void Manager::DestroyChunk(VIndex ind)
{
	for(int i = 0;i<registry.size();i++)
	{
		if(ind.Compare(registry[i])==true)
		{
			//destroythread=glfwCreateThread((GLFWthreadfun)ChunkDestroy,&chunks[i]);
			//ChunkDestroy(&chunks[i]);
			//delete chunks[i];
			chunks.erase(chunks.begin()+i);
			registry.erase(registry.begin()+i);
		}
	}
}
void Manager::Render()
{
	for(int i = 0;i<chunks.size();i++)
	{
		//if(chunks[i]!=nullptr)
		//{
			chunks[i].Render();
		//}
	}
}
Chunk* Manager::GetChunk(VIndex ind)
{
	for(int i=0;i<chunks.size();i++)
	{
		if(ind.Compare(&chunks[i].vindex)==true)
		{
			return &chunks[i];
		}
	}
	return nullptr;
}
Chunk* Manager::GetChunk(Vector3 vpos)
{
	VIndex ind;
	ind.x=floor(vpos.x/(float)VOX_VOXELSIZE_X);
	ind.y=floor(vpos.y/(float)VOX_VOXELSIZE_Y);
	ind.z=floor(vpos.z/(float)VOX_VOXELSIZE_Z);
	for(int i=0;i<chunks.size();i++)
	{
		if(ind.Compare(&chunks[i].vindex)==true)
		{
			return &chunks[i];
		}
	}
	return nullptr;
}
Voxel* Manager::GetVoxel(VIndex cind,VIndex vind)
{
	return &(GetChunk(cind)->voxels[vind.x][vind.y][vind.z]);
}
Voxel* Manager::GetVoxel(Vector3 vpos)
{
	VIndex cind;
	cind.x=floor(vpos.x/(float)VOX_VOXELSIZE_X);
	cind.y=floor(vpos.y/(float)VOX_VOXELSIZE_Y);
	cind.z=floor(vpos.z/(float)VOX_VOXELSIZE_Z);
	VIndex vind;
	vind.x=floor((int)vpos.x%VOX_VOXELSIZE_X);
	vind.y=floor((int)vpos.y%VOX_VOXELSIZE_Y);
	vind.z=floor((int)vpos.z%VOX_VOXELSIZE_Z);
	return &(GetChunk(cind)->voxels[vind.x][vind.y][vind.z]);
}

Chunk::Chunk(Manager* manage, VIndex* vind)
{
	manager=manage;
	vindex=vind;
	position.x=vind->x*VOX_VOXELSIZE_X;
	position.y=vind->y*VOX_VOXELSIZE_Y;
	position.z=vind->z*VOX_VOXELSIZE_Z;
	state=CHUNKSTATE::PREINIT;
}
void Chunk::Init()
{
	ChunkInit(this);
}
void Chunk::Destroy()
{
	ChunkDestroy(this);
}
void Chunk::Render()
{
	if(state==CHUNKSTATE::READY)
	{
		glPushMatrix();
		glTranslatef(vindex.x*VOX_VOXELSIZE_X,vindex.y*VOX_VOXELSIZE_Y,vindex.z*VOX_VOXELSIZE_Z);
		for(int i = 0;i<VOX_VOXELSIZE_X;i++)
		{
			for(int j = 0;j<VOX_VOXELSIZE_Y;j++)
			{
				for(int k = 0;k<VOX_VOXELSIZE_Z;k++)
				{
					voxels[i][j][k].Render();
				}
			}
		}
		glPopMatrix();
	}
}
void Chunk::Calculate()
{
	for(int i = 0;i<VOX_VOXELSIZE_X;i++)
	{
		for(int j = 0;j<VOX_VOXELSIZE_Y;j++)
		{
			for(int k = 0;k<VOX_VOXELSIZE_Z;k++)
			{
				voxels[i][j][k].Calculate();
			}
		}
	}
}

void Voxel::Init(Chunk* c,VIndex vpos)
{
	vind=vpos;
	position.x=(c->vindex.x*VOX_VOXELSIZE_X)+vind.x;
	position.y=(c->vindex.y*VOX_VOXELSIZE_Y)+vind.y;
	position.z=(c->vindex.z*VOX_VOXELSIZE_Z)+vind.z;
	v_density=c->manager->generator.GetLocation(position);
	v_vtype=VOXELTYPE::CUBE;
}
void Voxel::Render()
{
	if(v_vtype==VOXELTYPE::CUBE)
	{
		if(v_density>0.5f)
		{
			Draw::Cube(vind.x,vind.y,vind.z);
		}
	}
}
void Voxel::Calculate()
{
}