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
#include "water.h"
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
	Vector2& getInitMousePos() {
		return initMousePos;
	}
	int getSwings() {
		return swing;
	}
	void setSwing(int p_swing);
	void setVelocity(float x, float y);
	void setInitMousePos(float x, float y);
	void updateGame( bool mousestate1, bool mousestate2,float time,Goal target, std:: vector <Object> obstacle,std::vector<water> river, Mix_Chunk* golfhit, Mix_Chunk* goalhit, Mix_Chunk* watersound);
	void setInitVelocity(float x, float y);
	void setWinState(bool win);
	bool getWinState()
	{
		return winner;
	}

private:
	Vector2 goal;
	float vantoc;
	float vantocbandau;
	Vector2 velocity;
	Vector2 initMousePos;
	Vector2 initVelocity;
	int swing = 0;
	int vecy = 1;
	int vecx = 1;
	bool winner = false;
	bool accessible = true;
	bool chargedone = true;
	const float friction = 0.08;
	std::vector <Entity> arrow;
};