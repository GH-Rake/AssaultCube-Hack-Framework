#include "player.h"

//base functions to be overridden by inherited class

bool FW::Player_t::IsValid()
{
	if (health > 0 && state == ALIVE)
	{
		return true;
	}
	else return false;
}

void FW::Player_t::Calculate(Player_t localPlayer)
{
	dist = Distance(*localPlayer.pos, *pos);
	angleTo = CalcAngle(*localPlayer.pos, *pos);
	angleDiff = Distance(*localPlayer.angle, angleTo);
}

bool FW::Player_t::IsVisible(Player_t localPlayer)
{
	//stub for overridden function
	if (screen.iszero())
	{
		return false;
	}
	else return true;
}