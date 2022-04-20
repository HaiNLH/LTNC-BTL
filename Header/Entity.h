#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Math.h"

class Entity
{
public:
	Entity(Vector2 p_pos, SDL_Texture* p_tex);
	Vector2& getPos()
	{
		return pos;
	}
	void setPos(float x, float y);
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
private:
	Vector2 pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
}; 