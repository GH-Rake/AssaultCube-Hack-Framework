#pragma once
#include "Windows.h"
#include "mem.h"
#include "FW.h"
#include "AC_SDK.h"
#include "AC_player.h"

class AC_t : public FW::Aimbot_t
{
public:
	Menu_t* menu = nullptr;
	int viewport[4];

	Hack* keybinds;
	Hack* noScope;
	Hack* noRecoil;
	Hack* flyHack;
	//Hack * fullbright;
	//Hack * radarHack;

	bool bLocalGame = true;
	bool bTeamGame = false;
	bool bESP = false;
	bool bAimbot = false;
	bool bMenu = true;

	gameStatus_t gameStatus = GSTAT_GAME;
	sqr* world = (sqr*)0x50A1F8;
	int* sfactor = (int*)0x505BB4;
	int* lastmillis = (int*)0x509EAC;
	int* gameMode = (int*)(0x50F49C);
	int* numOfPlayers = (int*)(0x50f500);
	float* matrix = (float*)(0x501AE8);
	playerent* localPlayer = *(playerent * *)0x50F4F4;
	entList* ents = *(entList * *)0x50F4F8;

	int* p = *(int**)0x0;

	std::vector<row> HackMenu();
	void Load();
	void HackLoop();
	void ReadGame();
	void ReadPlayerData();
	void ReadHotKeys();
};