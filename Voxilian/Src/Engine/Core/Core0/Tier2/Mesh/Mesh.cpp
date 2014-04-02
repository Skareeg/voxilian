#include "Mesh.h"

XYZ VEC3(float px,float py,float pz)
{
	XYZ vec = {px,py,pz};
	return vec;
};

bool CMesh::AddCube(btVector3& pos,btVector3& size)
{
	SSubMesh newmesh;
	newmesh.name="Cube";
	newmesh.texture=0;
	float px = pos.x();
	float py = pos.y();
	float pz = pos.z();
	float sx = size.x()/2.0f;
	float sy = size.y()/2.0f;
	float sz = size.z()/2.0f;
	STriag tri[12];
	float sq = sqrtf(2.0f)/2.0f;
	{
		//BACK//
		tri[0].v[0]=VEC3(px-sx,py-sy,pz-sz);
		tri[0].v[1]=VEC3(px+sx,py-sy,pz-sz);
		tri[0].v[2]=VEC3(px+sx,py+sy,pz-sz);
		tri[1].v[0]=VEC3(px+sx,py+sy,pz-sz);
		tri[1].v[1]=VEC3(px-sx,py+sy,pz-sz);
		tri[1].v[2]=VEC3(px-sx,py-sy,pz-sz);
		//
		tri[0].n[0]=VEC3(-sq,-sq,-sq);
		tri[0].n[1]=VEC3(+sq,-sq,-sq);
		tri[0].n[2]=VEC3(+sq,+sq,-sq);
		tri[1].n[0]=VEC3(+sq,+sq,-sq);
		tri[1].n[1]=VEC3(-sq,+sq,-sq);
		tri[1].n[2]=VEC3(-sq,-sq,-sq);
		//
		tri[0].u[0]=VEC3(0,0,0);
		tri[0].u[1]=VEC3(1,0,0);
		tri[0].u[2]=VEC3(1,1,0);
		tri[1].u[0]=VEC3(1,1,0);
		tri[1].u[1]=VEC3(0,1,0);
		tri[1].u[2]=VEC3(0,0,0);
		//FRONT//
		tri[2].v[2]=VEC3(px-sx,py-sy,pz+sz);
		tri[2].v[1]=VEC3(px+sx,py-sy,pz+sz);
		tri[2].v[0]=VEC3(px+sx,py+sy,pz+sz);
		tri[3].v[2]=VEC3(px+sx,py+sy,pz+sz);
		tri[3].v[1]=VEC3(px-sx,py+sy,pz+sz);
		tri[3].v[0]=VEC3(px-sx,py-sy,pz+sz);
		//
		tri[2].n[2]=VEC3(-sq,-sq,+sq);
		tri[2].n[1]=VEC3(+sq,-sq,+sq);
		tri[2].n[0]=VEC3(+sq,+sq,+sq);
		tri[3].n[2]=VEC3(+sq,+sq,+sq);
		tri[3].n[1]=VEC3(-sq,+sq,+sq);
		tri[3].n[0]=VEC3(-sq,-sq,+sq);
		//
		tri[2].u[2]=VEC3(0,0,0);
		tri[2].u[1]=VEC3(1,0,0);
		tri[2].u[0]=VEC3(1,1,0);
		tri[3].u[2]=VEC3(1,1,0);
		tri[3].u[1]=VEC3(0,1,0);
		tri[3].u[0]=VEC3(0,0,0);
		//TOP//
		tri[4].v[0]=VEC3(px-sx,py-sy,pz-sz);
		tri[4].v[1]=VEC3(px+sx,py-sy,pz-sz);
		tri[4].v[2]=VEC3(px+sx,py-sy,pz+sz);
		tri[5].v[0]=VEC3(px+sx,py-sy,pz+sz);
		tri[5].v[1]=VEC3(px-sx,py-sy,pz+sz);
		tri[5].v[2]=VEC3(px-sx,py-sy,pz-sz);
		//
		tri[4].n[0]=VEC3(-sq,-sq,-sq);
		tri[4].n[1]=VEC3(+sq,-sq,-sq);
		tri[4].n[2]=VEC3(+sq,-sq,+sq);
		tri[5].n[0]=VEC3(+sq,-sq,+sq);
		tri[5].n[1]=VEC3(-sq,-sq,+sq);
		tri[5].n[2]=VEC3(-sq,-sq,-sq);
		//
		tri[4].u[0]=VEC3(0,0,0);
		tri[4].u[1]=VEC3(1,0,0);
		tri[4].u[2]=VEC3(1,1,0);
		tri[5].u[0]=VEC3(1,1,0);
		tri[5].u[1]=VEC3(0,1,0);
		tri[5].u[2]=VEC3(0,0,0);
		//BOTTOM//
		tri[6].v[2]=VEC3(px-sx,py+sy,pz-sz);
		tri[6].v[1]=VEC3(px+sx,py+sy,pz-sz);
		tri[6].v[0]=VEC3(px+sx,py+sy,pz+sz);
		tri[7].v[2]=VEC3(px+sx,py+sy,pz+sz);
		tri[7].v[1]=VEC3(px-sx,py+sy,pz+sz);
		tri[7].v[0]=VEC3(px-sx,py+sy,pz-sz);
		//
		tri[6].n[2]=VEC3(-sq,+sq,-sq);
		tri[6].n[1]=VEC3(+sq,+sq,-sq);
		tri[6].n[0]=VEC3(+sq,+sq,+sq);
		tri[7].n[2]=VEC3(+sq,+sq,+sq);
		tri[7].n[1]=VEC3(-sq,+sq,+sq);
		tri[7].n[0]=VEC3(-sq,+sq,-sq);
		//
		tri[6].u[2]=VEC3(0,0,0);
		tri[6].u[1]=VEC3(1,0,0);
		tri[6].u[0]=VEC3(1,1,0);
		tri[7].u[2]=VEC3(1,1,0);
		tri[7].u[1]=VEC3(0,1,0);
		tri[7].u[0]=VEC3(0,0,0);
		//LEFT//
		tri[8].v[0]=VEC3(px-sx,py-sy,pz-sz);
		tri[8].v[1]=VEC3(px-sx,py+sy,pz-sz);
		tri[8].v[2]=VEC3(px-sx,py+sy,pz+sz);
		tri[9].v[0]=VEC3(px-sx,py+sy,pz+sz);
		tri[9].v[1]=VEC3(px-sx,py-sy,pz+sz);
		tri[9].v[2]=VEC3(px-sx,py-sy,pz-sz);
		//
		tri[8].n[0]=VEC3(-sq,-sq,-sq);
		tri[8].n[1]=VEC3(-sq,+sq,-sq);
		tri[8].n[2]=VEC3(-sq,+sq,+sq);
		tri[9].n[0]=VEC3(-sq,+sq,+sq);
		tri[9].n[1]=VEC3(-sq,-sq,+sq);
		tri[9].n[2]=VEC3(-sq,-sq,-sq);
		//
		tri[8].u[0]=VEC3(0,0,0);
		tri[8].u[1]=VEC3(1,0,0);
		tri[8].u[2]=VEC3(1,1,0);
		tri[9].u[0]=VEC3(1,1,0);
		tri[9].u[1]=VEC3(0,1,0);
		tri[9].u[2]=VEC3(0,0,0);
		//RIGHT//
		tri[10].v[2]=VEC3(px+sx,py-sy,pz-sz);
		tri[10].v[1]=VEC3(px+sx,py+sy,pz-sz);
		tri[10].v[0]=VEC3(px+sx,py+sy,pz+sz);
		tri[11].v[2]=VEC3(px+sx,py+sy,pz+sz);
		tri[11].v[1]=VEC3(px+sx,py-sy,pz+sz);
		tri[11].v[0]=VEC3(px+sx,py-sy,pz-sz);
		//
		tri[10].n[2]=VEC3(+sq,-sq,-sq);
		tri[10].n[1]=VEC3(+sq,+sq,-sq);
		tri[10].n[0]=VEC3(+sq,+sq,+sq);
		tri[11].n[2]=VEC3(+sq,+sq,+sq);
		tri[11].n[1]=VEC3(+sq,-sq,+sq);
		tri[11].n[0]=VEC3(+sq,-sq,-sq);
		//
		tri[10].u[2]=VEC3(0,0,0);
		tri[10].u[1]=VEC3(1,0,0);
		tri[10].u[0]=VEC3(1,1,0);
		tri[11].u[2]=VEC3(1,1,0);
		tri[11].u[1]=VEC3(0,1,0);
		tri[11].u[0]=VEC3(0,0,0);
	}
	for(int i = 0;i<12;i++)
	{
		newmesh.triangles.push_back(tri[i]);
	}
	submeshes.push_back(newmesh);
	return true;
}
//Remember that indices in obj files start at freaking 1!!!!!!
bool CMesh::AddFile(string filename)
{
	string filepath = "";
	int removepoint = 0;
	for(int i = filename.size()-1;i>0;i--)
	{
		if(filename[i]=='\\')
		{
			removepoint=i;
		}
	}
	for(int i = 0;i<removepoint;i++)
	{
		filepath.push_back(filename[i]);
	}
	filepath+="\\";
	vector<SSubMesh> meshes;
	string prefix = "Models\\";
	string line = "";
	string mline = "";
	ifstream fileobj((prefix+filename).c_str(),ios::in);
	vector<XYZ> vecs;
	vector<XYZ> norms;
	vector<XYZ> uvs;
	bool go = getline(fileobj,line);
	bool skip = false;
	bool stop = false;
	string assoclib = "";
	while(go&&!stop)
	{
		if(line.size()>0)
		{
			skip=false;
			if(
				line[0]=='m'&&line[1]=='t'&&line[2]=='l'&&
				line[3]=='l'&&line[4]=='i'&&line[5]=='b'&&line[6]==' '
				)
			{
				string lib = "";
				for(int i = 7;i<line.size();i++)
				{
					lib.push_back(line[i]);
				}
				assoclib=lib;
								ifstream filemtl((prefix+filepath+lib).c_str(),ios::in);
								if(filemtl.is_open()==false)
								{
									cout<<"L";
								}
								vector<string> mtls;
								vector<string> texs;
								while(getline(filemtl,mline))
								{
									if(
										mline[0]=='n'&&mline[1]=='e'&&mline[2]=='w'&&
										mline[3]=='m'&&mline[4]=='t'&&mline[5]=='l'&&mline[6]==' '
										)
									{
										string mtl = "";
										for(int i = 7;i<mline.size();i++)
										{
											mtl.push_back(mline[i]);
										}
										mtls.push_back(mtl);
									}
									if(
										mline[0]=='m'&&mline[1]=='a'&&mline[2]=='p'&&
										mline[3]=='_'&&mline[4]=='K'&&mline[5]=='d'&&mline[6]==' '
										)
									{
										string tex = "";
										for(int i = 7;i<mline.size();i++)
										{
											tex.push_back(mline[i]);
										}
										texs.push_back(tex);
									}
								}
								string texprefix = "Models\\"+filepath;
								texs.resize(mtls.size());
								for(int i = 0;i<mtls.size();i++)
								{
									SetAlias(texprefix+texs[i],mtls[i],lib);
								}
								filemtl.close();
			}
			//This gets the vertices.
			if(line[0]=='v'&&line[1]==' ')
			{
				string sts[3];
				int num = -1;
				for(int i = 1;i<line.size();i++)
				{
					if(line[i]==' ')
					{
						num++;
					}
					else
					{
						sts[num].push_back(line[i]);
					}
				}
				vecs.push_back(VEC3(atof(sts[0].c_str()),atof(sts[1].c_str()),atof(sts[2].c_str())));
			}
			//This gets the normals.
			if(line[0]=='v'&&line[1]=='n'&&line[2]==' ')
			{
				string sts[3];
				int num = -1;
				for(int i = 2;i<line.size();i++)
				{
					if(line[i]==' ')
					{
						num++;
					}
					else
					{
						sts[num].push_back(line[i]);
					}
				}
				norms.push_back(VEC3(atof(sts[0].c_str()),atof(sts[1].c_str()),atof(sts[2].c_str())));
			}
			//This gets the texture coordinates.
			if(line[0]=='v'&&line[1]=='t'&&line[2]==' ')
			{
				string sts[2];
				int num = -1;
				for(int i = 2;i<line.size();i++)
				{
					if(line[i]==' ')
					{
						num++;
					}
					else
					{
						sts[num].push_back(line[i]);
					}
				}
				XYZ vec3 = VEC3(atof(sts[0].c_str()),atof(sts[1].c_str()),0);
				vec3.y+=1.0f;
				uvs.push_back(vec3);
			}
			if(line[0]=='g'&&line[1]==' ')
			{
				string nm = "";
				for(int i = 2;i<line.size();i++)
				{
					nm+=line[i];
				}
				SSubMesh newmesh;
				newmesh.name=nm;
				newmesh.texture=0;
				newmesh.matlib=assoclib;
				bool fgo = getline(fileobj,line);
				while(fgo&&!skip&&!stop)
				{
					if(line.size()>0)
					{
						if(
							line[0]=='u'&&line[1]=='s'&&line[2]=='e'&&
							line[3]=='m'&&line[4]=='t'&&line[5]=='l'&&line[6]==' '
							)
						{
							string mtl = "";
							for(int i = 7;i<line.size();i++)
							{
								mtl.push_back(line[i]);
							}
							newmesh.texture=SetTexture(mtl,newmesh.matlib);
						}
						if(line[0]=='f'&&line[1]==' ')
						{
							STriag tri;
							vector<string> ints[3];
							int num = -1;
							int fn = 0;
							for(int i = 1;i<line.size()&&num<3;i++)
							{
								if(line[i]==' '&&i<line.size()-1)
								{
									if(i<line.size()-2)
									{
										if(line[i+1]!=' ')
										{
											num++;
											fn=0;
											ints[num].push_back("");
										}
									}
								}
								else
								{
									if(line[i]=='/')
									{
										fn++;
										ints[num].push_back("");
									}
									else
									{
										ints[num][fn].push_back(line[i]);
									}
								}
							}
							for(int i = 0;i<3;i++)
							{
								tri.v[i]=vecs[atoi(ints[i][0].c_str())-1];
								if(fn>0)
								{
									tri.u[i]=uvs[atoi(ints[i][1].c_str())-1];
								}
								if(fn>1)
								{
									tri.n[i]=norms[atoi(ints[i][2].c_str())-1];
								}
							}
							newmesh.triangles.push_back(tri);
						}
						skip = (line[0]=='g'&&line[1]==' ');
						if(skip)
						{
							fgo=false;
						}
						else
						{
							fgo=true;
						}
					}
					stop=!getline(fileobj,line);
				}
				submeshes.push_back(newmesh);
			}
			if(skip)
			{
				go=true;
			}
			else
			{
				if(!stop)
				{
					go=getline(fileobj,line);
				}
			}
		}
		else
		{
			go=getline(fileobj,line);
		}
	}
	for(int i = 0;i<meshes.size();i++)
	{
		submeshes.push_back(meshes[i]);
	}
	fileobj.close();
	return true;
}
void CMesh::DrawMeshNoUVNoNormals()
{
	for(int m = 0;m<submeshes.size();m++)
	{
		glBindTexture(GL_TEXTURE_2D,0);
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f,1.0f,1.0f);
		for(int i = 0;i<submeshes[m].triangles.size();i++)
		{
			STriag t = submeshes[m].triangles[i];
			for(int j = 0;j<3;j++)
			{
				glVertex3f(t.v[j].x,t.v[j].y,t.v[j].z);
			}
		}
		glEnd();
	}
}
void CMesh::DrawMeshNoNormals()
{
	for(int m = 0;m<submeshes.size();m++)
	{
		unsigned int tex = submeshes[m].texture;
		if(tex>=0)
		{
			glBindTexture(GL_TEXTURE_2D,textures[submeshes[m].texture].texture);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D,0);
		}
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f,1.0f,1.0f);
		for(int i = 0;i<submeshes[m].triangles.size();i++)
		{
			STriag t = submeshes[m].triangles[i];
			for(int j = 0;j<3;j++)
			{
				glTexCoord2f(t.u[j].x,t.u[j].y);
				glVertex3f(t.v[j].x,t.v[j].y,t.v[j].z);
			}
		}
		glEnd();
	}
}
void CMesh::DrawMeshNoUV()
{
	for(int m = 0;m<submeshes.size();m++)
	{
		glBindTexture(GL_TEXTURE_2D,0);
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f,1.0f,1.0f);
		for(int i = 0;i<submeshes[m].triangles.size();i++)
		{
			STriag t = submeshes[m].triangles[i];
			for(int j = 0;j<3;j++)
			{
				glNormal3f(t.n[j].x,t.n[j].y,t.n[j].z);
				glVertex3f(t.v[j].x,t.v[j].y,t.v[j].z);
			}
		}
		glEnd();
	}
}
void CMesh::DrawMesh()
{
	for(int m = 0;m<submeshes.size();m++)
	{
		unsigned int tex = submeshes[m].texture;
		if(tex>=0)
		{
			glBindTexture(GL_TEXTURE_2D,textures[submeshes[m].texture].texture);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D,0);
		}
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f,1.0f,1.0f);
		for(int i = 0;i<submeshes[m].triangles.size();i++)
		{
			STriag t = submeshes[m].triangles[i];
			for(int j = 0;j<3;j++)
			{
				glTexCoord2f(t.u[j].x,t.u[j].y);
				glNormal3f(t.n[j].x,t.n[j].y,t.n[j].z);
				glVertex3f(t.v[j].x,t.v[j].y,t.v[j].z);
			}
		}
		glEnd();
	}
}
unsigned int CMesh::SetTexture(string texturename,string mtllib)
{
	for(int i = 0;i<textures.size();i++)
	{
		for(int j = 0;j<textures[i].mataliases.size();j++)
		{
			if(textures[i].matlibs[j]==mtllib)
			{
				if(textures[i].mataliases[j]==texturename)
				{
					return i;
				}
			}
		}
	}
	return -1;
}
void CMesh::SetAlias(string texturefile,string alias,string matlib)
{
	for(int i = 0;i<textures.size();i++)
	{
		if(textures[i].name==texturefile)
		{
			for(int j = 0;j<textures[i].mataliases.size();j++)
			{
				if(textures[i].mataliases[j]==alias&&textures[i].matlibs[j]==matlib)
				{
					Graphics.FreeTexture(textures[i].texture);
					textures[i].texture=Graphics.LoadTexture(texturefile,false,false);
					return;
				}
			}
			textures[i].mataliases.push_back(alias);
			textures[i].matlibs.push_back(matlib);
			return;
		}
	}
	STexture tex;
	tex.texture=Graphics.LoadTexture(texturefile,false,false);
	tex.name=texturefile;
	tex.mataliases.push_back(alias);
	tex.matlibs.push_back(matlib);
	textures.push_back(tex);
	return;
}