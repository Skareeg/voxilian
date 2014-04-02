#ifndef H_GAME
#define H_GAME
#include "..\Engine\Core\Globals.h"
#include "..\Engine\Core\Core.h"

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