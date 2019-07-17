#pragma once
#include "windows.h"
#include "geom.h"

enum state_t { ALIVE, DEAD, SPECTATOR };

namespace FW
{
	//minimum needed for aimbot/ESP
	class Player_t
	{
	public:
		//variables to pull from memory
		vec3* pos, * head, * angle, * velocity;
		int* health;
		state_t state;
		int team;
		char name[16];

		//hack variables to be calculated
		bool bEnemy;
		float dist;
		float angleDiff;
		vec3 angleTo;
		vec3 screen = vec3();
		bool bValid;
		bool bVisible;

		//default to be overridden in derived classes
		bool IsValid();
		virtual bool IsVisible(Player_t localPlayer);
		void Calculate(Player_t localPlayer);
	};
}