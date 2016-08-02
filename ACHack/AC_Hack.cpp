#include "AC_Hack.h"

void AC_t::ReadPlayerData()
{
	FW::Aimbot_t::localPlayer = AC_Player_t(this->localPlayer, bTeamGame, localPlayer->team, matrix, viewport[2], viewport[3], localPlayer);//change this

	FW::Aimbot_t::players.clear();

	for (int i = 0; i < (*numOfPlayers); i++)
	{
		auto e = ents->ents[i];
		if (!e || !e->vTable) continue;
		if (e->vTable == 0x4E4A98 || e->vTable == 0x4E4AC0)
		{
			players.push_back(AC_Player_t(e, bTeamGame, localPlayer->team, matrix, viewport[2], viewport[3], localPlayer));
		}
	}

	for (auto &p : players)
	{
		p.Calculate(FW::Aimbot_t::localPlayer);
	}
}


void AC_t::HackLoop()
{
	glGetIntegerv(GL_VIEWPORT, viewport);
	HDC currentHDC = wglGetCurrentDC();

	if (!menu || !menu->bMenuBuilt)
	{
		menu = new Menu_t;
		menu->BuildMenu(HackMenu(), viewport[2] * 0.50, viewport[3] * 0.01);
		menu->bMenuBuilt = true;
	}

	if (!menu->font.bBuilt || currentHDC != menu->font.hdc)
	{
		menu->font.Build(MENU_FONT_HEIGHT);
	}

	if (gameStatus == GSTAT_GAME)
	{

		ReadGame();
		ReadPlayerData();

		if (bESP)
		{
			GL::SetupOrtho();
			FW::ESP::ESP(players, matrix, viewport[2], viewport[3], menu->font);
			GL::RestoreGL();
		}

		if (bLocalGame)
		{
			localPlayer->health = 999;
			*localPlayer->weapon->ammo = 999;
		}
	}

	ReadHotKeys();

	if (bMenu)
	{
		menu->Draw();
	}
}

AC_t * AC = nullptr;


//wglSwapBuffers Hook
GL::twglSwapBuffers owglSwapBuffers;
BOOL __stdcall hwglSwapBuffers(HDC hDc)
{
	AC->HackLoop();
	return owglSwapBuffers(hDc);
}

void AC_t::Load()
{
	menu = new Menu_t;

	StartShootThread(&bAimbot);

	keybinds = new Hack(0x045F920, "\x90\x90\x90\x90\x90\x90");
	noScope = new Hack(0x463CEB, "\x90\x90\x90\x90\x90");
	noRecoil = new Hack(0x463786, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90");
	flyHack = new Hack(0x45ADD8, "\x01");
	//radarHack = new Hack((void*))
	//fullbright = new Hack((void*))

	keybinds->Enable();
	GL::Hook("wglSwapBuffers", (uintptr_t &)owglSwapBuffers, &hwglSwapBuffers);
}

std::vector<row> AC_t::HackMenu()
{
	std::vector<row> rows;
	rows.push_back(row(M_HEADER, "Dragnipur V2.0", nullptr));
	rows.push_back(row(M_FUNCTION, "[F1] Aimbot   : ", &bAimbot));
	rows.push_back(row(M_FUNCTION, "[F2] ESP      : ", &bESP));
	rows.push_back(row(M_FUNCTION, "[F3] NoRecoil : ", &noRecoil->bStatus));
	rows.push_back(row(M_FUNCTION, "[F4] FlyHack  : ", &flyHack->bStatus));
	rows.push_back(row(M_FUNCTION, "[F5] NoScope  : ", &noScope->bStatus));
	rows.push_back(row(M_FUNCTION, "[INS]Hide Menu", nullptr));
	rows.push_back(row(M_FOOTER, "GuidedHacking.com", nullptr));
	return rows;
};

void AC_t::ReadGame()
{
	if ((*gameMode == 0 || *gameMode == 4 || *gameMode == 5 || *gameMode == 7 || *gameMode == 11 || *gameMode == 13 || 
		 *gameMode == 14 || *gameMode == 16 || *gameMode == 17 || *gameMode == 20 || *gameMode == 21))
	{
		bTeamGame = true;
	}
	else bTeamGame = false;

	if (*gameMode == 7 || *gameMode == 8 || *gameMode == 12 || (*gameMode >= 18 && *gameMode <= 21))
	{
		bLocalGame = true;
	}
	else bLocalGame = false;
}

void AC_t::ReadHotKeys()
{
	if (GetFocus() == FindWindowA(0, "AssaultCube"))
	{
		//if key is not pressed, target unlock
		if (!(GetAsyncKeyState(VK_RBUTTON)) & 1)
		{
			bTargetLock = false;
		}

		if (GetAsyncKeyState(VK_RBUTTON) && bAimbot)
		{
			GetTarget(FW::Aimbot_t::localPlayer);

			if (target)//good here
			{
				localPlayer->angle = target->angleTo;
				bAttack = true;
			}
		}

		if (GetAsyncKeyState(VK_F1) & 1)
		{
			bAimbot = !bAimbot;
		}

		if (GetAsyncKeyState(VK_F2) & 1)
		{
			bESP = !bESP;
		}

		if (GetAsyncKeyState(VK_F3) & 1)
		{
			noRecoil->Toggle();
		}

		if (GetAsyncKeyState(VK_F4) & 1)
		{
			flyHack->Toggle();
		}

		if (GetAsyncKeyState(VK_F5) & 1)
		{
			noScope->Toggle();
		}

		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			bMenu = !bMenu;
		}
	}
}