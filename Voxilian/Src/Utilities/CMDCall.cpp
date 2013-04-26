#include "CMDCall.h"
CMDCall g_cmd;
int g_callindex;
CallItem::CallItem()
{
	ID=g_callindex;
	g_callindex++;
	type="";
}
void CallItem::Clear()
{
	xint.clear();
	xfloat.clear();
}
void CallItem::ClearInt()
{
	xint.clear();
}
void CallItem::ClearFloat()
{
	xfloat.clear();
}
CallStack::CallStack()
{
	name="";
}
void CallStack::Clear()
{
	calls.clear();
}
CMDCall::CMDCall()
{
	g_callindex=0;
	CallStack* stack = new CallStack();
	stack->name="main";
	stacks.push_back(*stack);
}
using namespace std;
void CMDCall::Call(std::string callname,std::string calltype,std::vector<int> callints,std::vector<float> callfloats)
{
	for(int b = 0;b<stacks.size();b++)
	{
		if(stacks[b].name==callname)
		{
			CallItem c;
			stacks[b].calls.push_back(c);
			stacks[b].calls.back().ID=g_callindex;
			g_callindex++;
			stacks[b].calls.back().type=calltype;
			stacks[b].calls.back().xint=callints;
			stacks[b].calls.back().xfloat=callfloats;
			cout<<"Call - "<<callname<<":"<<calltype<<" - Success.\n";
			return;
		}
	}
	cout<<"Call - "<<callname<<":"<<calltype<<" - Fail.\n";
	return;
}
void CMDCall::Call(std::string callname,CallItem callitem)
{
	for(int b = 0;b<stacks.size();b++)
	{
		if(stacks[b].name==callname)
		{
			CallItem c;
			stacks[b].calls.push_back(c);
			stacks[b].calls.end()->ID=g_callindex;
			g_callindex++;
			stacks[b].calls.end()->type=callitem.type;
			stacks[b].calls.end()->xint=callitem.xint;
			stacks[b].calls.end()->xfloat=callitem.xfloat;
			cout<<"Call - "<<callname<<":"<<callitem.type<<" - Success.\n";
			return;
		}
	}
	cout<<"Call - "<<callname<<":"<<callitem.type<<" - Fail.\n";
	return;
}
CallItem CMDCall::GetNextCall(std::string callname)
{
	CallItem defret;
	defret.ID=-1;
	defret.type="NONE";
	for(int b = 0;b<stacks.size();b++)
	{
		if(stacks[b].name==callname)
		{
			if(stacks[b].calls.size()>0)
			{
				return stacks[b].calls[0];
			}
		}
	}
	return defret;
}
void CMDCall::DeleteNextCalls()
{
	for(int b = 0;b<stacks.size();b++)
	{
		if(stacks[b].calls.size()>0)
		{
			stacks[b].calls.rbegin();
		}
	}
}