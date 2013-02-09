#ifndef TH
#define TH
#include <math.h>
#include <vector>
#include <GL\glfw.h>
typedef struct
{
	float x;
	float y;
	float z;
} Vector3;

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
#endif