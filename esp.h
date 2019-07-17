#pragma once
#include "hackgl.h"
#include "gltext.h"
#include "player.h"

namespace FW
{
	namespace ESP
	{
		void DrawBox(FW::Player_t p, vec3 screen, GL::Font& font, int windowWidth);
		void ESP(std::vector<FW::Player_t> players, float matrix[16], int windowWidth, int windowHeight, GL::Font& font);
	}
}