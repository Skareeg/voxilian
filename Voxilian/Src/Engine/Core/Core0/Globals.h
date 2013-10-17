#ifndef H_GLB
#define H_GLB

#define PI 3.14159265359f
#define E 2.71828182845904523536028747135266249775724709369995f
#define RNDACC 100000.0f

#include <Windows.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <fmod.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
namespace Function
{
	btVector3 QuatToEuler(btQuaternion& quat);
	btVector3 QuatRotVec(btVector3& vec,btQuaternion& quat);
	btQuaternion QuatConjugate(btQuaternion& quat);
	namespace String
	{
		string CreateFromInt(int n);
	};
	void Clamp(float* f,float min,float max);
	void Clamp(int* f,int min,int max);
};
string str(int n);
float rnd();
int filereadint(ifstream* f);
string filereadstring(ifstream* f,int length);
float filereadfloat(ifstream* f);
#endif