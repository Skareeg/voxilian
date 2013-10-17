#include "Command.h"
#include "..\..\Core0.h"
void CCommand::Add(string command)
{
	CCMD cmd = {command,false,false};
	commands.push_back(cmd);
}
void CCommand::Register(string command,void* func)
{
	CCommandable cmd = {command,func};
	callbacks.push_back(cmd);
}
void CCommand::Frame()
{
}