#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Math.h"

class ui :public Entity
{
public:
	ui(Vector2 p_pos, SDL_Texture* p_tex);
	bool inside(int x, int y);
	SDL_Rect& clip(bool inside);
private:
	const int UI_FRAME = 2;
	SDL_Rect gSpriteClips[2];
};