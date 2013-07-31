#ifndef H_LOG
#define H_LOG
#include "..\..\Globals.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>

class CLog
{
public:
	std::vector<std::string> logs;
	ofstream files[10];
	CLog();
	void Log(std::string log,int level);
};

extern CLog Log;

#endif