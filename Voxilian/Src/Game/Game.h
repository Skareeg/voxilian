#ifndef H_GAME
#define H_GAME
#include "Core\Tier1.h"
#include "Core\Tier2.h"
#include "Core\Tier3.h"
#include "Game\UI\Menu.h"

class Game
{
public:
	bool isRunning;
	bool terminated;
	CScene* sc_MainMenu;
	CScene* sc_GameWorld;
	void Init();
	void Run();
	void Terminate();
};

#endif