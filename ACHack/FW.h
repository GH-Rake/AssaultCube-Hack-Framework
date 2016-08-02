#pragma once
#include <Windows.h>
#include <thread>
#include "menu.h"
#include "aimbot.h"
#include "esp.h"

enum gameStatus_t
{
	GSTAT_LOBBY, GSTAT_GAME
};

namespace FW
{
	class Game
	{
	public:
		int windowWidth, windowHeight;
		//what else?
	};

};