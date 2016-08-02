#pragma once
#include "windows.h"
#include <vector>

namespace mem
{
	//Doesn't work if your pattern contains 0xff
	byte* FindPattern(byte pattern[], int length, byte* begin, byte* end);
	//Find all matching patterns
	std::vector<byte*> FindPatterns(byte pattern[], int length, byte* begin, byte* end);

	bool Hook(void * toHook, void * ourFunct, int len);
	void * TrampolineHook(void * toHook, void * ourFunct, int len);
	void Patch(uintptr_t* dst, uintptr_t* src, int size);
};

class Hack
{
public:
	char* name;
	bool bStatus;
	uintptr_t address;
	byte newBytes[20];
	byte oldBytes[20];
	int size;

	Hack(uintptr_t address, char* newBytes);
	void Enable();
	void Disable();
	void Toggle();
};