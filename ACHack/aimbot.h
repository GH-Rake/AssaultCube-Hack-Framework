#pragma once
#include "Windows.h"
#include <vector>
#include <thread>
#include "geom.h"
#include "player.h"

namespace FW
{
	class Aimbot_t
	{
	public:
		bool bTargetLock = false;
		bool bAttack = false;
		vec3_t crossHair;

		Player_t localPlayer;
		std::vector<Player_t> players;
		std::vector<Player_t *> targets;
		Player_t * target = nullptr;

		void StartShootThread(bool * bAimbot);
		void GetCrossHair(int viewport[4]);
		void MoveMouse(vec3_t point, int windowWidth, int windowHeight);
		void GetTarget(Player_t localPlayer);
	};

	void ShootThread(Aimbot_t * aimbot, bool * bAimbot);
	bool SortByAngle(Player_t *lhs, Player_t *rhs);
}