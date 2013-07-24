#ifndef H_GAME
#define H_GAME
#include "Core\Tier1.h"
#include "Core\Tier2.h"

class Game
{
public:
	bool isRunning;
	void Init();
	void Run();
	void Terminate();
};

#endif