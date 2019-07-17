#pragma once
//Thank you c5 for your help!
#include <windows.h>
#include <stdio.h>
#include <gl\GL.h>
#include "geom.h"

namespace GL
{
	class Font
	{
	public:
		bool bBuilt = false;
		unsigned int base;
		HDC hdc = nullptr;
		int height;
		int width;

		void Build(int height);
		void Print(float x, float y, const unsigned char color[3], const char* format, ...);

		//center on X and Y axes
		vec3 centerText(float x, float y, float width, float height, float textWidth, float textHeight);
		//center on X axis only
		float centerText(float x, float width, float textWidth);
	};
};