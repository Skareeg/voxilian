#include "Log.h"

CLog::CLog()
{
	bad = false;
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
	CLCMD lg = {log,level};
	logs.push_back(lg);
}
void CLog::Send()
{
	while(logs.size()>0)
	{
		string log = logs.at(0).log;
		int level = logs.at(0).level;
		if(!bad)
		{
			if(level>=0&&level<10)
			{
				static int lognumber = 0;
				files[level]<<lognumber<<":"<<log.c_str()<<"\n";
				cout<<lognumber<<":"<<"W"<<level<<"->"<<log.c_str()<<"\n";
				/*for(int i = 0;i<level;i++)
				{
					files[i]<<lognumber<<":"<<"{LogW"<<level<<"}\n";
				}*/
				lognumber++;
			}
			else
			{
				Log("INCORRECT LOG LEVEL",0);
			}
		}
		else
		{
			cout<<"NO LOG AVAILABLE!\n";
		}
		logs.erase(logs.begin());
	}
}
CLog Log;