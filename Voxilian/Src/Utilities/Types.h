#ifndef TH
#define TH
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <GL\glfw.h>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

using namespace std;

class LogFile
{
public:
	ofstream LogF;
	LogFile();
	void Log(string st);
	void Log(float st);
};

/*typedef struct
{
	float x;
	float y;
	float z;
} Vector3;*/

class Vector3
{
public:
	float x;
	float y;
	float z;
	Vector3();
	Vector3 operator+(Vector3);
	Vector3 operator-(Vector3);
	Vector3 operator*(Vector3);
	Vector3 operator/(Vector3);
	btVector3 GetBullet();
	void CoutShow();
};

typedef struct {
   Vector3 p[3];
   Vector3 n[3];
} Triangle;

typedef struct {
   Vector3 p[8];
   float val[8];
} VoxelCell;

class Entity;
class Camera;
class Player;

namespace VMath
{
	float Distance(Vector3 v1,Vector3 v2);
	Vector3 Vector(float x,float y,float z);
}
namespace VoxelFunc
{
	//This is the MC Algorithm implementor.
	int Polygonise(VoxelCell grid,double isolevel,std::vector<Triangle> *triangles);
	//This interpolates (smooths) out the vectors.
	Vector3 VertexInterp(float isolevel,Vector3 p1,Vector3 p2,float valp1,float valp2);
	//This may or may not be used for normals.
	Vector3 CrossProduct(Vector3 v1,Vector3 v2);
	//This may or may not be used for normals.
	Vector3 Normalize(Vector3 v);
}

#endif