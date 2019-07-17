#pragma once
#include "menu.h"

float fWindowScale;
bool bMenu = true;

void Menu_t::GetMenuWidth()
{
	longRowStrLen = 0;
	for (auto r : rows)
	{
		int len;
		if (r.type == M_FUNCTION && r.status != nullptr)
		{
			len = strlen(r.text) + strlen(r.text2);
		}
		else
		{
			len = strlen(r.text);
		}

		if (len > longRowStrLen)
		{
			longRowStrLen = len;
		}
	}
	width = (longRowStrLen * MENU_FONT_WIDTH) + (MENU_ROW_XBUFFER);
}

void Menu_t::BuildMenu(std::vector<row> newRows, float x2, float y2)
{
	x = x2;
	y = y2;

	height = 0;
	nextRowY = y;

	for (auto r : newRows)
	{
		r.pmenu = this;
		rows.push_back(r);
	}

	GetMenuWidth();
}

void Menu_t::Draw()
{
	GL::SetupOrtho();
	for (row r : rows)
	{
		r.Draw();
		nextRowY += r.height;
		r.pmenu->height += r.height;
	}

	GL::DrawOutline(x, y, width, height, MENU_LINE_WIDTH, rgb::black);
	GL::RestoreGL();
	height = 0;
	nextRowY = y;
}

row::row(rowtype_t type, char* text, bool* status)
{
	this->type = type;
	this->text = text;
	this->status = status;

	this->height = MENU_FONT_HEIGHT + (MENU_ROW_YBUFFER * 2);

	if (type == M_FOOTER || type == M_HEADER)
	{
		this->height += MENU_LINE_WIDTH / 2;
	}

	else if (status != nullptr)
	{
		if (*status)
		{
			text2 = "ON";
		}
		else text2 = "OFF";
	}
}

void row::Draw()
{
	GL::DrawFilledRect(pmenu->x, pmenu->nextRowY, pmenu->width, height, rgb::gray);

	if (type == M_FOOTER || type == M_HEADER)
	{
		GL::DrawOutline(pmenu->x, pmenu->nextRowY, pmenu->width, height, MENU_LINE_WIDTH, rgb::black);
		pmenu->nextRowY += MENU_LINE_WIDTH / 2;
	}

	if (type == M_FUNCTION)
	{
		vec3 pos = pmenu->font.centerText(pmenu->x, pmenu->nextRowY, pmenu->width, height, pmenu->width - MENU_ROW_XBUFFER, MENU_FONT_HEIGHT);

		if (status != nullptr)
		{
			if (*status)
			{
				text2 = "ON";
			}
			else text2 = "OFF";
			pmenu->font.Print(pos.x, pos.y, MENU_FONT_COLOR, "%s%s", text, text2);
		}
		else pmenu->font.Print(pos.x, pos.y, MENU_FONT_COLOR, "%s", text, text2);
	}

	else
	{
		vec3 pos = pmenu->font.centerText(pmenu->x, pmenu->nextRowY, pmenu->width, height, strlen(text) * MENU_FONT_WIDTH, MENU_FONT_HEIGHT);
		pmenu->font.Print(pos.x, pos.y, MENU_FONT_COLOR, "%s", text);
	}
}