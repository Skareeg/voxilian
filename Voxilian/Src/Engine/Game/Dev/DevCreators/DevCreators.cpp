#include "DevCreators.h"
#include "..\DevSys.h"

void CDevCreator::Init(CDevSystem* devsys)
{
	devsystem=devsys;
	devmode=false;
}
void CDevCreator::Frame()
{
	if(devmode)
	{
	}
	else
	{
		devsystem->devinfo.push_back("Press F2 for DevCreator info.");
	}
}
void CDevCreator::Terminate()
{
}