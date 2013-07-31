#include "Log.h"

CLog::CLog()
{
	bool bad = false;
	for(int i = 0;i<10;i++)
	{
		char* num = new char[4];
		_itoa_s(i,num,4,10);
		string st = "Logs\\LogW";
		files[i].open(st+num+".txt",ios::out|ios::trunc);
		if(!files[i].is_open())
		{
			cout<<"LOGERROR->file_LogW"<<i<<"_cannot_be_opened!\n";
			bad=true;
		}
	}
	if(bad)
	{
		cout<<"Attention! Please recreate folder \"Logs\" at\ngame executable or close errored files!\n";
	}
}
void CLog::Log(std::string log,int level)
{
	if(level>=0&&level<10)
	{
		static int lognumber = 0;
		files[level]<<lognumber<<":"<<log.c_str()<<"\n";
		cout<<lognumber<<":"<<"W"<<level<<"->"<<log.c_str()<<"\n";
		for(int i = 0;i<level;i++)
		{
			files[i]<<lognumber<<":"<<"{LogW"<<level<<"}\n";
		}
		lognumber++;
	}
	else
	{
		Log("INCORRECT LOG LEVEL",0);
	}
}

CLog Log;