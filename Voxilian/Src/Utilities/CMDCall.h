#ifndef CMDCall_h
#define CMDCall_h
#include <vector>
#include <string>
#include <iostream>
class CallItem
{
public:
	int ID;
	std::string type;
	std::vector<int> xint;
	std::vector<float> xfloat;
	CallItem();
	void Clear();
	void ClearInt();
	void ClearFloat();
};
class CallStack
{
public:
	std::string name;
	std::vector<CallItem> calls;
	CallStack();
	void Clear();
};
//Main function call class.
class CMDCall
{
public:
	//The callstacks, or groups. "main" is created at startup.
	std::vector<CallStack> stacks;
	//The constructor for the CMDCall class.
	CMDCall();
	//Creates a new call. In this sense, calls a function from the game somewhere.
	void Call(std::string callname,std::string calltype,std::vector<int> callints,std::vector<float> callfloats);
	//Creates a new call. In this sense, calls a function from the game somewhere.
	void Call(std::string callname,CallItem callitem);
	//Gets the next call from the selected stack.
	CallItem GetNextCall(std::string callname);
	//Deletes the next call from all stacks. This is to be run after all updating for everthing else.
	void DeleteNextCalls();
};
//Global function call.
extern CMDCall g_cmd;
//Global call index.
extern int g_callindex;
#endif