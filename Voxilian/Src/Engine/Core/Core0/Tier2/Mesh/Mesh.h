#ifndef H_MESH
#define H_MESH

#include "..\..\Tier1\Tier1.h"

struct XYZ
{
	float x;
	float y;
	float z;
};
XYZ VEC3(float px,float py,float pz);

struct STriag
{
	XYZ v[3];
	XYZ n[3];
	XYZ u[3];
};

struct SSubMesh
{
	vector<STriag> triangles;
	string name;
	string matlib;
	unsigned int texture;
};
struct STexture
{
	unsigned int texture;
	string name;
	vector<string> mataliases;
	vector<string> matlibs;
};

class CMesh
{
public:
	vector<SSubMesh> submeshes;
	CMesh();
	vector<STexture> textures;
	bool AddCube(btVector3& pos,btVector3& size);
	bool AddFile(string filename);
	void DrawMeshNoUVNoNormals();
	void DrawMeshNoNormals();
	void DrawMeshNoUV();
	void DrawMesh();
	unsigned int SetTexture(string texturename,string mtllib);
	void SetAlias(string texturefile,string alias,string lib);
};

#endif