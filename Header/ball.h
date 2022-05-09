#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_mixer.h>

#include "Entity.h"
#include "Math.h"
#include "Goal.h"
#include "object.h"
class Ball :public Entity {
public:
	Ball(Vector2 p_pos, SDL_Texture* p_tex,SDL_Texture* arrow_tex);
	Vector2& getVelocity()
	{
		return velocity;
	}
	std::vector<Entity> getArrow()
	{
		return arrow;
	}
	//dang bi thừa
	Vector2& getInitMousePos() {
		return initMousePos;
	}
	void setVelocity(float x, float y);
	void setInitMousePos(float x, float y);
	void updateGame( bool mousestate1, bool mousestate2,float time,Goal target, Object obstacle, Mix_Chunk* golfhit, Mix_Chunk* goalhit);
	void setInitVelocity(float x, float y);
	void setWinState(bool win);
	bool getWinState()
	{
		return winner;
	}

private:
	Vector2 goal;//wasted
	float vantoc;
	float vantocbandau;
	Vector2 velocity;
	Vector2 initMousePos;
	Vector2 initVelocity;
	int vecy = 1;
	int vecx = 1;
	bool winner = false;
	bool accessible = true;
	bool chargedone = true;
	const float friction = 0.08;
	//Entity arrow;
	std::vector <Entity> arrow;
};