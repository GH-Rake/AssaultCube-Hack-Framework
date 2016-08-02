#pragma once
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>
#include <gl\GL.h>
#include "geom.h"
#include "mem.h"

namespace rgb
{
	const GLubyte red[3] = { 255, 0, 0 };
	const GLubyte green[3] = { 0, 255, 0 };
	const GLubyte gray[3] = { 55, 55, 55 };
	const GLubyte lightgray[3] = { 192, 192, 192 };
	const GLubyte black[3] = { 0, 0, 0 };
}

namespace GL
{
		//GLint viewport[4];
		
		void Hook(char* function, uintptr_t  &oFunction, void * hFunction);

		void SetupOrtho();
		void RestoreGL();

		void DrawFilledRect(float x, float y, float width, float height, const GLubyte color[3]);
		void DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3]);

		typedef BOOL(__stdcall * twglSwapBuffers) (_In_ HDC hDc);


}