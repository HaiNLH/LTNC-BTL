#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <math.h>


#include "ball.h"
#include "Entity.h"
#include "Math.h"
#include "Goal.h"

Ball::Ball(Vector2 p_pos, SDL_Texture* p_tex)
	:Entity(p_pos, p_tex)
{
}


void Ball::setInitMousePos(float x, float y)
{
	initMousePos.x = x;
	initMousePos.y = y;
}
void Ball::setVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}
void Ball :: setInitVelocity(float x, float y) {
	initVelocity.x = x;
	initVelocity.y = y;
}
void Ball::updateGame(bool mousestate1, bool mousestate2, float time, Goal target)
{
	if (winner)
	{
		std::cerr << "YOU'RE THE WINNER!!!!!!! CONGRATS!!!!!!!!!!!!!!!!!!!";
		winner = false;
	}
	if (getPos().x >= target.getPos().x-24 && getPos().x <= target.getPos().x+24 && getPos().y >= target.getPos().y-24  && getPos().y <= target.getPos().y +24)
	{	
		if (vantoc > 80) winner = false;
		else {
			winner = true;
			setPos(355, 800);
			vantoc = 0;
			//setVelocity(0,0);
		}
	}
	if (mousestate1)
	{
		int mouseX, mouseY;	
		SDL_GetMouseState(&mouseX, &mouseY);
		setInitMousePos(mouseX, mouseY);
	
	}
	if (mousestate2)
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		vantoc=sqrt(pow(initMousePos.x-mouseX,2)+pow(initMousePos.y-mouseY,2)); // equal to distance between initmouse and downmouse
		vantocbandau = vantoc;
		setVelocity((mouseX - initMousePos.x)/-100, (mouseY - initMousePos.y)/-100);
		setInitVelocity((mouseX - initMousePos.x) / -100, (mouseY - initMousePos.y) / -100);
	}
	
	else 
	{
		if (velocity.x < 0) vecx = -1;
		else vecx = 1;
		if (velocity.y < 0)vecy = -1;
		else vecy = 1;

		setPos(getPos().x + getVelocity().x * time, getPos().y + getVelocity().y * time);
		if ( getVelocity().x > 0.0001 || getVelocity().x < -0.0001 || getVelocity().y > 0.0001 || getVelocity().y < -0.0001)
		{

			if (vantoc > 0)
			{
				vantoc -= friction * time;
				std::cerr << vantoc << std::endl;
			}
			else if(vantoc<=0)
			{
				vantoc = 0;
			}
			velocity.x = (vantoc / vantocbandau)*abs(initVelocity.x) * vecx;
			velocity.y = (vantoc / vantocbandau) * abs(initVelocity.y) * vecy;
			
		}
		if (getPos().x < 0) 
		{
			setVelocity(abs(getVelocity().x), getVelocity().y);

		}
		else if (getPos().y < 0)
		{
			setVelocity(getVelocity().x, abs(getVelocity().y));

		}
		else if (getPos().x > 690)
		{
			setVelocity(-abs(getVelocity().x),getVelocity().y);

		}
		else if (getPos().y > 1050)
		{
			setVelocity(getVelocity().x, -abs(getVelocity().y));
		}
	}
}