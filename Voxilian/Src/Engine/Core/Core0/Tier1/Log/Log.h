#ifndef H_LOG
#define H_LOG
#include <GL\glfw.h>
#include "..\..\Globals.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>

struct CLCMD
{
	string log;
	int level;
};

class CLog
{
public:
	bool bad;
	std::vector<CLCMD> logs;
	ofstream files[10];
	int lognumber;
	CLog();
	void Log(std::string log,int level);
	void Send();
};
extern CLog Log;

#endif