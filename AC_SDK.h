#pragma once
#include <Windows.h>
#include <vector>
#include "geom.h"

//#define PLAYER_HEIGHT 5.25
//#define HALF_PLAYER_WIDTH 1

enum gameModes
{
	TEAMDEATHMATCH = 0,
	COOPEDIT,
	DEATHMATCH,
	SURVIVOR,
	TEAMSURVIVOR,
	CTF,
	PISTOLFRENZY,
	BOTTEAMDEATHMATCH,
	BOTDEATHMATCH,
	LASTSWISSSTANDING,
	ONESHOTONEKILL,
	TEAMONESHOTONEKILL,
	BOTONESHOTONEKILL,
	HUNTTHEFLAG,
	TEAMKEEPTHEFLAG,
	KEEPTHEFLAG,
	TEAMPF,
	TEAMLSS,
	BOTPISTOLFRENZY,
	BOtlSS,
	BOTTEAMSURVIVOR,
	BOTTEAMONESHOTONEKILL,
	NUM
};

#define m_teammode    (*gameMode==0 || *gameMode==4 || *gameMode==5 || *gameMode==7 || *gameMode==11 || *gameMode==13 || *gameMode==14 || *gameMode==16 || *gameMode==17 || *gameMode==20 || *gameMode==21)
#define m_botmode     (*gameMode==7 || *gameMode == 8 || *gameMode==12 || (*gameMode>=18 && *gameMode<=21))
#define m_flags       (*gameMode==5 || *gameMode==13 || *gameMode==14 || *gameMode==15)

enum mapEntTypes
{
	NOTUSED = 0,
	LIGHT = 1,                      // lightsource, attr1 = radius, attr2 = intensity
	PLAYERSTART = 2,                // attr1 = angle, attr2 = team
	I_CLIPS = 3,
	I_AMMO = 4,
	I_GRENADE = 5,
	I_HEALTH = 6,
	I_HELMET = 7,
	I_ARMOUR = 8,
	I_AKIMBO = 9,
	MAPMODEL = 10,                   // attr1 = angle, attr2 = idx, attr3 = elevation, attr4 = texture
	CARROT = 11,
	LADDER = 12,
	CTF_FLAG = 13,                   // attr1 = angle, attr2 = red/blue
	SOUND = 14,
	CLIP = 15,                       // attr1 = elevation, attr2 = xradius, attr3 = yradius, attr4 = height
	PLCLIP = 16,                     // attr1 = elevation, attr2 = xradius, attr3 = yradius, attr4 = height
	MAXENTTYPES = 17
};

class mapEnt
{
public:
	__int16 x; //0x0000
	__int16 y; //0x0002
	__int16 z; //0x0004
	__int16 attr1; //0x0006
	unsigned char type; //0x0008
	unsigned char attr2; //0x0009
	unsigned char attr3; //0x000A
	unsigned char attr4; //0x000B
	unsigned char bSpawned; //0x000C
	int lastmillis; //0x000D
	unsigned char padding[3];
};//Size=0x0014

class playerent;

class weapon
{
public:
	char pad_0x0000[0x4]; //0x0000
	__int32 ID; //0x0004
	playerent* owner; //0x0008
	uintptr_t* guninfo; //0x000C
	int* ammo2; //0x0010
	int* ammo; //0x0014
	int* gunWait;
	int shots;
	int breload;
};

class playerent
{
public:
	DWORD vTable; //0x0
	vec3 head; //0x0004
	char _0x0010[36];
	vec3 pos; //0x0034
	vec3 angle; //0x0040
	char _0x004C[37];
	BYTE bScoping; //0x0071
	char _0x0072[134];
	__int32 health; //0x00F8
	__int32 armor; //0x00FC
	char _0x0100[292];
	BYTE bAttacking; //0x0224
	char name[16]; //0x0225
	char _0x0235[247];
	BYTE team; //0x032C
	char _0x032D[11];
	BYTE state; //0x0338
	char _0x0339[59];
	weapon* weapon; //0x0374
	char _0x0378[520];
};

struct entList
{
	playerent* ents[31];
};

class flagEnt
{
public:
	__int32 team; //0x0000
	mapEnt* mapent; //0x0004
	__int32 number; //0x0008
	playerent* player; //0x000C
	vec3 pos; //0x0010
	__int32 state; //0x001C
	__int32 unknown2; //0x0020
};//Size=0x0024

class flagArray
{
public:
	flagEnt flags[2]; //0x0000
};//Size=0x0048

struct sqr
{
	unsigned char type;
	char floor, ceil;
	unsigned char wtex, ftex, ctex;
	unsigned char r, g, b;
	unsigned char vdelta;
	char defer;
	char occluded;
	unsigned char utex;
	unsigned char tag;
	unsigned char reserved[2];
};

struct traceresult_s
{
	vec3 end;
	bool collided;
};