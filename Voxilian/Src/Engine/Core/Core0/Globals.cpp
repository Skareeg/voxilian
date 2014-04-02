#include "Globals.h"
btVector3 Function::QuatToEuler(btQuaternion& quat)
{
	float x = quat.getX();
	float y= quat.getY();
	float z = quat.getZ();
	float w = quat.getW();
	float nsp = ((x*y)+(z*w));
	float yaw = 0.0f;
	float pitch = 0.0f;
	float roll = 0.0f;
	//pitchYawRoll.Y = (float)atan2f(2.0f * q.X * q.W + 2f * q.Y * q.Z, 1 - 2f * (sqz  + sqw));     // Yaw 
	//pitchYawRoll.X = (float)asinf(2.0f * ( q.X * q.Z - q.W * q.Y ) );                             // Pitch 
	//pitchYawRoll.Z = (float)atan2f(2.0f * q.X * q.Y + 2f * q.Z * q.W, 1 - 2f * (sqy + sqz));      // Roll
	//euler.Z = (irr::f32) (atan2(2.0 * (x*y + z*w),(sqx - sqy - sqz + sqw)) * (180.0f/irr::core::PI));
    //euler.X = (irr::f32) (atan2(2.0 * (y*z + x*w),(-sqx - sqy + sqz + sqw)) * (180.0f/irr::core::PI));          
    //euler.Y = (irr::f32) (asin(-2.0 * (x*z - y*w)) * (180.0f/irr::core::PI));
	
	yaw = asinf(2.0f * (x*z - w*y));
	pitch = atan2f(2.0f * (y*z + x*w),(sqrt(x)-sqrt(y)-(sqrt(z)+sqrt(w))));
	roll = atan2f(2.0f * (x*y + z*w),(-sqrt(x)-sqrt(y)+(sqrt(z)+sqrt(w))));

	/*bank = asinf(
		(2.0f*x*y)+(2.0f*z*w));
	if(nsp>-0.5f&&nsp<0.5f)
	{
		heading = atan2f(
			(2.0f*x*w)-(2.0f*y*z),
			1.0f-(2.0f*(powf(y,2.0f)))-(2.0f*(powf(z,2.0f))));
		altitude = atan2f(
			(2.0f*x*w)-(2.0f*y*z),
			1.0f-(2.0f*(powf(x,2.0f)))-(2.0f*(powf(z,2.0f))));
	}
	else
	{
		altitude = 0.0f;
		float mult = 2.0f;
		if(nsp<0)
		{
			mult*=-1.0f;
		}
		heading = mult*atan2f(x,w);
	}*/
	return btVector3(pitch,yaw,roll);
	//float sqw = s*s;  
	/*btVector3 euler;
	btQuaternion nquat = cquat;
	nquat.normalize();
	btVector3 quat = nquat.getAxis();
		float sqx = quat.x()*quat.x();    
		float sqy = quat.y()*quat.y();    
		float sqz = quat.z()*quat.z();

		bool homogenous = true;

		if (homogenous) {
			euler.setX(atan2f(2.0f * (quat.x()*quat.y() + quat.z()*quat.w()), sqx - sqy - sqz + sqrt(quat.w())));    		
			euler.setY(asinf(-2.0f * (quat.x()*quat.z() - quat.y()*quat.w())));
			euler.setZ(atan2f(2.0f * (quat.y()*quat.z() + quat.x()*quat.w()), -sqx - sqy + sqz + sqrt(quat.w())));    
		} else {
			euler.setX(atan2f(2.0f * (quat.z()*quat.y() + quat.x()*quat.w()), 1.0f - 2.0f*(sqx + sqy)));
			euler.setY(asinf(-2.0f * (quat.x()*quat.z() - quat.y()*quat.w())));
			euler.setZ(atan2f(2.0f * (quat.x()*quat.y() + quat.z()*quat.w()), 1.0f - 2.0f*(sqy + sqz)));
		}
		/*
	euler.x = atan2f(2.f * (v.z*v.y + v.x*s), 1 - 2* (sqx + sqy));
	euler.y = asinf(-2.f * (v.x*v.z - v.y*s));
	euler.z = atan2f(2.f * (v.x*v.y + v.z*s), 1 - 2* (sqy + sqz));*/
		//return euler;
}
btVector3 Function::QuatRotVec(btVector3& vec,btQuaternion& quat)
{
	btQuaternion V(vec, 0.0f);
	btQuaternion conj = QuatConjugate(quat);
	btQuaternion res = (quat * V * conj);
	return btVector3(res.x(),res.y(),res.z());
}
btQuaternion Function::QuatConjugate(btQuaternion& quat)
{
	return btQuaternion(-quat.x(),-quat.y(),-quat.z(),quat.w());
}
string Function::String::CreateFromInt(int n)
{
	char ch[24];
	_itoa_s(n,ch,10);
	string st = ch;
	return st;
}
string str(int n)
{
	return Function::String::CreateFromInt(n);
}
float rnd()
{
	return (float)((float)(rand()%(int)RNDACC)/(float)RNDACC);
}
int filereadint(ifstream* f)
{
	int r = 0;
	f->read((char*)(&r),sizeof(int));
	return r;
}
string filereadstring(ifstream* f,int length)
{
	char* c = new char[length];
	f->read(c,length);
	string r = c;
	return r;
}
float filereadfloat(ifstream* f)
{
	float r = 0;
	f->read((char*)(&r),sizeof(float));
	return r;
}
void Function::Clamp(float* f,float min,float max)
{
	if(*f<min)
	{
		*f=min;
	}
	if(*f>max)
	{
		*f=max;
	}
}