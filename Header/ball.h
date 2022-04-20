#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "Entity.h"
#include "Math.h"
#include "Goal.h"

class Ball :public Entity {
public:
	Ball(Vector2 p_pos, SDL_Texture* p_tex);
	Vector2& getVelocity()
	{
		return velocity;
	}
	//dang bi thừa
	Vector2& getInitMousePos() {
		return initMousePos;
	}
	void setVelocity(float x, float y);
	void setInitMousePos(float x, float y);
	void updateGame(bool mousestate1, bool mousestate2,float time,Goal target); 
	void setInitVelocity(float x, float y);
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
	const float friction = 0.05;

};