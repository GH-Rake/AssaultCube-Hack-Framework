#pragma once
#include <Windows.h>
#include "AC_Hack.h"

extern AC_t * AC;

DWORD __stdcall Init(LPVOID param)
{
	AC = new AC_t;
	AC->Load();

	return 0;
}

BOOL __stdcall DllMain(HINSTANCE hModule, uintptr_t  dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, Init, nullptr, 0, nullptr);
		DisableThreadLibraryCalls(hModule);
		break;

	case DLL_PROCESS_DETACH:
		break;

	default:
		break;
	}
	return true;
}