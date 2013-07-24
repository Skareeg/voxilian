#include "Log.h"

void CLog::Log(std::string log,int level)
{
	std::cout<<"W"<<level<<"->"<<log.c_str()<<"\n";
}

CLog Log;