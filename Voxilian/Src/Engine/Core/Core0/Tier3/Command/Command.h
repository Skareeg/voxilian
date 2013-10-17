#ifndef H_CMDS
#define H_CMDS

#include "..\..\Globals.h"
#include "..\..\Tier1.h"
#include "..\..\Tier2.h"

struct CCMD
{
	string cmd;
	bool complete;
	bool started;
};
struct CCommandable
{
	string name;
	(void*) func;
};

class CCommand
{
public:
	vector<CCMD> commands;
	vector<CCommandable> callbacks;
	void Add(string command);
	void Register(string command,void* func);
	void Frame();
};
extern CCommand Command;

#endif