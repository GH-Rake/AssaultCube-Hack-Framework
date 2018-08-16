#include "AC_player.h"

//create a AC_Player_t based on reclass ent
//localPlayer
AC_Player_t::AC_Player_t(playerent* ent)
{
	pos = &ent->pos;
	head = &ent->head;
	angle = &ent->angle;
	//*velocity = ent->velocity; add later
	health = &ent->health;
	if (ent->state == 0)
	{
		state = ALIVE;
	}
	else state = DEAD;
}

AC_Player_t::AC_Player_t(playerent* ent, bool bTeamGame, int localTeam, float * matrix, int windowWidth, int windowHeight, playerent * localPlayer)
{
	pos = &ent->pos;
	head = &ent->head;
	angle = &ent->angle;
	//*velocity = ent->velocity; add later
	strcpy(name, ent->name);
	health = &ent->health;
	team = ent->team;

	//seperate into seperate functions?

	if (bTeamGame == true && ent->team == localTeam)
	{
		bEnemy = false;
	}
	else bEnemy = true;

	if (ent->state == 0)
	{
		state = ALIVE;
	}
	else state = DEAD;

	WorldToScreen(*pos, screen, matrix, windowWidth, windowHeight);

	bVisible = IsVisible(localPlayer);
}

//good
/*
bool AC_Player_t::IsVisible(playerent * localEnt)
{
uintptr_t traceLine = 0x048a310;
traceresult_s traceresult;
traceresult.collided = false;
vec3 from = localEnt->head;
vec3 to = *head;

__asm
{
push 0; bSkipTags
push 0; bCheckPlayers
push localEnt
push to.z
push to.y
push to.x
push from.z
push from.y
push from.x
lea eax, [traceresult]
call traceLine;
add esp, 36
}
return !traceresult.collided;
}
*/

bool AC_Player_t::IsVisible(playerent * localent)
{
	uintptr_t traceLine = 0x048a310;
	traceresult_s traceresult;
	traceresult.collided = false;
	vec3 from = localent->head;
	vec3 to = *head;

	__asm
	{
		push 0; bSkipTags
		push 0; bCheckPlayers
		//push localent
		push 0
		push to.z
		push to.y
		push to.x
		push from.z
		push from.y
		push from.x
		lea eax, [traceresult]
		call traceLine;
		add esp, 36
	}
	return !traceresult.collided;
}