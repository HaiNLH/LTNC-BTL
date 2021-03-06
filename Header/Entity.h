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
	float getAngle()
	{
		return angle;
	}
	Vector2 getScale()
	{
		return scale;
	}
	void setScale(float x, float y);
	void setAngle(float p_angle);
	void setPos(float x, float y);
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
private:
	Vector2 pos;
	Vector2 scale = Vector2(1, 1);
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	float angle;
}; 