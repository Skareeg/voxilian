#include "VOX.h"

#define VACCESS(a) a.x][a.y][a.z
#define VNLOOP1 for(int i=-1;i<=1;i++){for(int j=-1;j<=1;j++){for(int k=-1;k<=1;k++){
#define VNLOOP2 }}}
#define VLOOP1 for(int i=0;i<V_C_SIZEX;i++){for(int j=0;j<V_C_SIZEY;j++){for(int k=0;k<V_C_SIZEZ;k++){
#define VLOOP2 }}}
#define VNIJK i+1][j+1][k+1
#define VIJK i][j][k
#define L ;LOG
#define NM(st,name) LOG("VManager: "+name+": "+st)

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

void VManager::Init(Camera* c)
{
	LOG("Hi! This is the VManager. I am ready to begin construction.\n");
	cameraposition=&(c->pos);
	dimensia = new VDimensia(this,"Main");
	dimensias.push_back(dimensia);
	glCullFace(GL_BACK);
	time_t t;
	time(&t);
	srand(t);
}
void VManager::Update()
{
	dimensia->Update();
	glfwPollEvents();
	if(glfwGetKey('F')==GLFW_PRESS)
	{
		glS.ShowCursor(true);
		int choice;
		cout<<"CMD Now Ready!\n"
			<<"0:Quit.\n"
			<<"1:Create new dimensia.\n"
			<<"2:Switch to dimensia.\n";
		cin>>choice;
		while(choice!=0)
		{
			if(choice==1)
			{
				string nname;
				cout<<"Enter a name for the new dimensia->";
				cin>>nname;
				dimensias.push_back(new VDimensia(this,nname));
				LOG("VManager: User created new dimensia "+nname+".\n");
			}
			else if(choice==2)
			{
				int nd = 0;
				cout<<"Pick a dimension:\n";
				for(int i = 0;i<dimensias.size();i++)
				{
					cout<<i<<":"<<dimensias[i]->name<<"\n";
				}
				cin>>nd;
				while(nd>=dimensias.size()||nd<0)
				{
					cout<<"Enter a dimensia number between 0 and "<<dimensias.size()<<"!\n";
					cin>>nd;
				}
				dimensia=dimensias[nd];
				LOG("VManager: I switched to dimensia "+dimensia->name+".\n");
			}
			else
			{
				cout<<"Invalid Command Entered!\n";
			}
			cin>>choice;
		}
		glS.ShowCursor(false);
	}
}

void DimensiaInit(VDimensia* vd)
{
	vd->mindist=1;
	vd->maxdist=2;
	vd->state=1;
	NM("Dimensia Init Success!\n",vd->name);
}
void PushBackVoxelChunk(VDimensia* vd,VIndex cam,VIndex pos)
{
	VChunk* vc = new VChunk();
	vc->Init(vd,cam+pos);
	//vc.Neighbors();
	//vc.VNeighbors();
	/*VNLOOP1
		if(vc.neighbors[VNIJK]!=nullptr)
		{
			vc.neighbors[VNIJK]->Neighbors();
		}
		if(vc.neighbors[VNIJK]!=nullptr)
		{
			vc.neighbors[VNIJK]->VNeighbors();
		}
	VNLOOP2*/
	vd->index.push_back(cam+pos);
	vd->chunks_c.push_back(vc);
	NM("VChunk at <",vd->name)L(vc->position.x)L(":")L(vc->position.y)L(":")L(vc->position.z)L(">.\n");
}
void DimensiaCreate(VDimensia* vd)
{
	VIndex camindex;
	camindex.FromVector3(*(vd->manager->cameraposition));
	camindex.x/=V_C_SIZEX;
	camindex.y/=V_C_SIZEY;
	camindex.z/=V_C_SIZEZ;
	for(int i = -vd->mindist;i<=vd->mindist;i++)
	{
		for(int j = -vd->mindist;j<=vd->mindist;j++)
		{
			for(int k = -vd->mindist;k<=vd->mindist;k++)
			{
				bool good = true;
				for(int l = 0;l<vd->index.size();l++)
				{
					if(vd->index[l].Compare(camindex+VINDEX(i,j,k))==true)
					{
						good=false;
					}
				}
				if(good==true)
				{
					PushBackVoxelChunk(vd,camindex,VINDEX(i,j,k));
				}
			}
		}
	}
}
void DimensiaDestroy(VDimensia* vd)
{
	VIndex camindex;
	camindex.FromVector3(*(vd->manager->cameraposition));
	camindex.x/=V_C_SIZEX;
	camindex.y/=V_C_SIZEY;
	camindex.z/=V_C_SIZEZ;
	int sz = vd->chunks_r.size();
	for(int i = 0;i<sz;i++)
	{
		bool delchunk = false;
		if(vd->chunks_r[i]->position.x<camindex.x-vd->maxdist)
		{
			delchunk=true;
		}
		if(vd->chunks_r[i]->position.y<camindex.y-vd->maxdist)
		{
			delchunk=true;
		}
		if(vd->chunks_r[i]->position.z<camindex.z-vd->maxdist)
		{
			delchunk=true;
		}
		if(vd->chunks_r[i]->position.x>camindex.x+vd->maxdist)
		{
			delchunk=true;
		}
		if(vd->chunks_r[i]->position.y>camindex.y+vd->maxdist)
		{
			delchunk=true;
		}
		if(vd->chunks_r[i]->position.z>camindex.z+vd->maxdist)
		{
			delchunk=true;
		}
		if(delchunk==true)
		{
			VCInd v;
			v.number=i;
			v.size=sz;
			if(vd->chunks_r[i]->delflag!=true)
			{
				vd->chunks_r[i]->delflag=true;
				vd->chunks_d.push_back(i);
			}
		}
	}
}
void DelChunk(VChunk* chunk)
{
	delete chunk;
}

VDimensia::VDimensia(VManager* m,string nname)
{
	name=nname;
	manager=m;
	state=0;
	rndvec.x=rand()%1024;
	rndvec.y=rand()%1024;
	rndvec.z=rand()%1024;
	NM("This is "+name+". Construction was successful. I am ready to begin.\n",name);
	NM("Random vector set at: <",name)L(rndvec.x)L(",")L(rndvec.y)L(",")L(rndvec.z)L(">.\n");
}
void VDimensia::Update()
{
	if(state==0)
	{
		if(glfwWaitThread(createthread,GLFW_NOWAIT)==GL_TRUE)
		{
			createthread=glfwCreateThread((GLFWthreadfun)DimensiaInit,this);
		}
	}
	else if(state==1)
	{
		if(chunks_c.size()>0)
		{
			chunks_r.push_back(chunks_c[chunks_c.size()-1]);
			chunks_c.pop_back();
			NM("VChunk placed successfully.\n",name);
		}
		if(glfwWaitThread(createthread,GLFW_NOWAIT)==GL_TRUE)
		{
			createthread=glfwCreateThread((GLFWthreadfun)DimensiaCreate,this);
		}
		if(glfwWaitThread(destroythread,GLFW_NOWAIT)==GL_TRUE)
		{
			while(chunks_d.size()>0)
			{
				glfwCreateThread((GLFWthreadfun)DelChunk,chunks_r[chunks_d[chunks_d.size()-1]]);
				chunks_r.erase(chunks_r.begin()+chunks_d[chunks_d.size()-1]);
 				chunks_d.pop_back();
			}
			destroythread=glfwCreateThread((GLFWthreadfun)DimensiaDestroy,this);
		}
		for(int i = 0;i<chunks_r.size();i++)
		{
			chunks_r[i]->Render();
		}
	}
}
VChunk* VDimensia::GetChunk(VIndex vind)
{
	for(int i = 0;i<index.size();i++)
	{
		if(index[i].Compare(vind)==true)
		{
			return chunks_c[i];
		}
	}
	return nullptr;
}

void VChunk::Init(VDimensia* dm,VIndex indpos)
{
	position=indpos;
	dimensia=dm;
	delflag=false;
	/*VLOOP1
		voxels[VIJK].Init(this);
		vpointers.push_back(&voxels[VIJK]);
	VLOOP2*/
}
void VChunk::Update()
{
	/*for(int i = 0;i<vpointers.size();i++)
	{
		vpointers[i]->Update();
	}*/
}
void VChunk::Calculate()
{
	/*for(int i = 0;i<vpointers.size();i++)
	{
		vpointers[i]->Calculate();
	}*/
}
void VChunk::Render()
{
	glPushMatrix();
	glPushMatrix();
	glTranslatef(position.x*V_C_SIZEX,position.y*V_C_SIZEY,position.z*V_C_SIZEZ);
	glScalef(V_C_SIZEX/2,V_C_SIZEY/2,V_C_SIZEZ/2);
	Draw::Cube(0,0,0);
	glPopMatrix();
	glTranslatef(position.x*V_C_SIZEX,position.y*V_C_SIZEY,position.z*V_C_SIZEZ);
	/*for(int i = 0;i<vpointers.size();i++)
	{
		vpointers[i]->Render();
	}*/
	glPopMatrix();
}
void VChunk::Neighbors()
{
	/*VNLOOP1
		neighbors[VNIJK]=nullptr;
		VIndex nvi = VINDEX(i,j,k)+position;
		for(int l = 0;l<dimensia->index.size();l++)
		{
			if(dimensia->index[l].Compare(nvi)==true)
			{
				neighbors[VNIJK]=&(dimensia->chunks_u[l]);
			}
		}
	VNLOOP2*/
}
void VChunk::VNeighbors()
{
	/*VLOOP1
		voxels[VIJK].Neighbors();
	VLOOP2*/
}

void VVoxel::Init(VChunk* ch,VIndex pos)
{
	chunk=ch;
	position=pos;
	type=V_TYPE_CUBE;
}
void VVoxel::Calculate()
{
	mesh.clear();
	if(type==V_TYPE_CUBE)
	{
	}
}
void VVoxel::Render()
{
	Draw::Cube(position.x,position.y,position.z);
}
void VVoxel::Neighbors()
{
}