#ifndef VOX_H
#define VOX_H
#include "..\..\Utilities\Types.h"
#include <vector>
#include <string>
#include "..\..\Utilities\simplexnoise.h"
#include <ctime>
#include "..\..\Utilities\GLSYS.h"

#define VOX_VOXELSIZE_X 5
#define VOX_VOXELSIZE_Y 5
#define VOX_VOXELSIZE_Z 5

//GLFW HAZZ MULTITHREADZING SUPPORRRTTTTTTZZZZZZ?!?

//Voxel spacial classes.
namespace Spacial
{
	enum VOXELTYPE
	{
		CUBE,
		SMOOTH
	};
	enum CHUNKSTATE
	{
		PREINIT,
		READY,
		DESTROY
	};
	//Voxel has transform.
	class Transform;
	//Voxel index transform.
	class VIndex;

	class WorldGen;

	//Voxel chunk manager.
	class Manager;
	//Voxel manager chunk.
	class Chunk;
	//Voxel chunk voxel.
	class Voxel;
	//Voxel cell grid.
	class VCell;

	namespace Math
	{
		//This is the MC Algorithm implementor.
		int Polygonise(VCell grid,double isolevel,std::vector<Triangle> *triangles);
		//This interpolates (smooths) out the vectors.
		Vector3 VertexInterp(float isolevel,Vector3 p1,Vector3 p2,float valp1,float valp2);
		//This may or may not be used for normals.
		Vector3 CrossProduct(Vector3 v1,Vector3 v2);
		//This may or may not be used for normals.
		Vector3 Normalize(Vector3 v);
	};

	class Transform
	{
	public:
		Vector3 position;
		Vector3 size;
		Vector3 rotation;
	};
	class VIndex
	{
	public:
		int x;
		int y;
		int z;
		bool Compare(VIndex* v);
		VIndex();
		VIndex(Vector3 v);
		VIndex(VIndex* v);
		VIndex(int i,int j,int k);
	};
	static VIndex* VINDEX(int i,int j,int k);
	class VCell
	{
	public:
		Vector3 p[8];
		float d[8];
	};

	class WorldGen
	{
	public:
		void Init();
		int GetLocation(int x,int y);
	};

	class Manager
	{
	public:
		WorldGen generator;
		Vector3* cpos;
		float mindist;
		float maxdist;
		vector<VIndex*> registry;
		vector<Chunk*> chunks;
		vector<Chunk*> destroy;
		vector<Chunk*> create;
		void Init(Vector3* cm);
		void Update();
		GLFWthread mainthread;
		GLFWthread renderthread;
		void Render();
	};
	class Chunk : public Transform
	{
	public:
		int state;
		Manager* manager;
		Voxel*** voxels;
		VIndex* vindex;
		vector<Voxel*> updatevoxels;
		Chunk(Manager* manage, VIndex* vind);
		void Init();
		void Destroy();
		void Update();
		void Render();
	};
	class Voxel : public Transform
	{
	public:
		Chunk* chunk;
		VCell vcell;
		float v_density;
		float v_temperature;
		int v_vtype;
		VIndex vind;
		void Init(Chunk* c,VIndex vpos);
		void Calculate();
		void Render();
	};
};
#endif