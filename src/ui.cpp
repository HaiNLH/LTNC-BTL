#pragma once
#include "ui.h"
ui::ui(Vector2 p_pos, SDL_Texture* p_tex)
	:Entity(p_pos, p_tex) {}
bool ui::inside(int x, int y)
{	
	if (x > getPos().x && x<getPos().x + getCurrentFrame().w && y>getPos().y && y < getPos().y + getCurrentFrame().h)
	{
		std::cerr << "MARKED" << std::endl;
		return true;

	}
	else return false;
}
SDL_Rect& ui:: clip(bool inside)
{	
	gSpriteClips[0].x = 0;
	gSpriteClips[0].y = 0;
	gSpriteClips[0].w = getCurrentFrame().w;
	gSpriteClips[0].h = getCurrentFrame().h;

	gSpriteClips[1].x = getCurrentFrame().w/2;
	gSpriteClips[1].y = 0;
	gSpriteClips[1].w = getCurrentFrame().w;
	gSpriteClips[1].h = getCurrentFrame().h;
	if (inside)
	{
		return gSpriteClips[1];
	}
	else
		return gSpriteClips[0];
}