#ifndef H_LOG
#define H_LOG
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

class CLog
{
public:
	std::vector<std::string> logs;
	void Log(std::string log,int level);
};

extern CLog Log;

#endif