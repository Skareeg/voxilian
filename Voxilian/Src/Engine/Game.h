#ifndef H_GAME
#define H_GAME
#include "Core\Globals.h"
#include "Core\Core.h"

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