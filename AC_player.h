#pragma once
#include "player.h"
#include "AC_SDK.h"

class AC_Player_t : public FW::Player_t
{
public:
	AC_Player_t(playerent* ent); //local
	AC_Player_t(playerent* ent, bool bTeamGame, int localTeam, float* matrix, int windowWidth, int windowHeight, playerent* localPlayer);

	virtual bool IsVisible(playerent* localPlayer);
	bool IsValid();
};