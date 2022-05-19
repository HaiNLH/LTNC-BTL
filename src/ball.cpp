#include <iostream>
#include <vector>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>


#include "ball.h"
#include "Entity.h"
#include "Math.h"
#include "Goal.h"
#include "object.h"

Ball::Ball(Vector2 p_pos, SDL_Texture* p_tex, SDL_Texture* arrow_tex)
	:Entity(p_pos, p_tex)
{
	arrow.push_back(Entity(Vector2(-64, -64), arrow_tex));
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
void Ball::setWinState(bool win)
{
	winner = win;
}
void Ball::setSwing(int p_swing)
{
	swing = p_swing;
}
void Ball::updateGame( bool mousestate1, bool mousestate2, float time, Goal target,std:: vector <Object> obstacle, Mix_Chunk* golfhit, Mix_Chunk* goalhit)
{	
	if (winner)
	{
		if (getPos().x < goal.x)
		{
			setPos(getPos().x += 0.1 * time, getPos().y);
		}
		else if (getPos().x > goal.x)
		{
			setPos(getPos().x -= 0.1 * time, getPos().y);
		}
		if (getPos().y < goal.y)
		{
			setPos(getPos().x, getPos().y += 0.1 * time);
		}
		else if (getPos().y > goal.y)
		{
			setPos(getPos().x, getPos().y -= 0.1 * time);
		}
		//tPos(goal.x + 24, goal.y + 24);
		
		setScale(getScale().x - 0.001 * time, getScale().y - 0.001 * time);
	}
	if (getPos().x >= target.getPos().x-24 && getPos().x <= target.getPos().x+24 && getPos().y >= target.getPos().y-24  && getPos().y <= target.getPos().y +24)
	{	
		if (vantoc > 100) winner = false;
		else {
			
			winner = true;
			Mix_PlayChannel(-1, goalhit, 0);
			goal.x = target.getPos().x + 16;
			goal.y = target.getPos().y + 16;
			//level++;
			vantoc = 0;
			//setVelocity(0,0);
		}
	}
	if (mousestate1 && accessible)
	{

		int mouseX, mouseY;	
		SDL_GetMouseState(&mouseX, &mouseY);
		std::cerr << mouseX << "____" << mouseY << std::endl;
		setInitMousePos(mouseX, mouseY);
		chargedone = false;
	
	}
	if (mousestate2 && accessible)
	{	
		
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		vantoc=sqrt(pow(initMousePos.x-mouseX,2)+pow(initMousePos.y-mouseY,2)); // equal to distance between initmouse and downmouse
		vantocbandau = vantoc;
		setVelocity((mouseX - initMousePos.x)/-100, (mouseY - initMousePos.y)/-100);
		setInitVelocity((mouseX - initMousePos.x) / -100, (mouseY - initMousePos.y) / -100);
		arrow.at(0).setPos(getPos().x, getPos().y -32);
		arrow.at(0).setAngle(SDL_atan2(velocity.y, velocity.x) * (180 / 3.1415) + 90);
		if (vantoc>200)
		{
			vantoc= 200;
			vantocbandau = 200;
		}
		
	}
	
	else 
	{	
		if (!chargedone) {
			Mix_PlayChannel(-1, golfhit, 0);
			chargedone = true;
			swing++;
		}
		if (velocity.x < 0) vecx = -1;
		else vecx = 1;
		if (velocity.y < 0)vecy = -1;
		else vecy = 1;
		arrow.at(0).setPos(-64, -64);
		accessible = false;
		setPos(getPos().x + getVelocity().x * time, getPos().y + getVelocity().y * time);
		if ( getVelocity().x > 0.0001 || getVelocity().x < -0.0001 || getVelocity().y > 0.0001 || getVelocity().y < -0.0001)
		{

			if (vantoc > 0)
			{
				vantoc -= friction * time;
			}
			else if(vantoc<=0)
			{
				vantoc = 0;

			}
			velocity.x = (vantoc / vantocbandau)*abs(initVelocity.x) * vecx;
			velocity.y = (vantoc / vantocbandau) * abs(initVelocity.y) * vecy;
			
		}
		else {
			accessible = true;
		}
		if (getPos().x < 0) 
		{

			setVelocity(abs(getVelocity().x), getVelocity().y);

		}
		else if (getPos().y < 0)
		{	
			setVelocity(getVelocity().x, abs(getVelocity().y));
			
		}
		else if (getPos().x > 610)
		{	
			setVelocity(-abs(getVelocity().x),getVelocity().y);
			
		}
		else if (getPos().y > 930)
		{
			
			setVelocity(getVelocity().x, -abs(getVelocity().y));

		}
		for (Object& o : obstacle)
		{
			float mPosX = getPos().x + getVelocity().x * time;
			if (mPosX +32> o.getPos().x && mPosX<o.getPos().x + o.getCurrentFrame().w && getPos().y + 32 >o.getPos().y && getPos().y<o.getPos().y + o.getCurrentFrame().h)
			{
				setVelocity(  getVelocity().x*-1, getVelocity().y);
			}
		
			float mPosY = getPos().y + getVelocity().y * time;
			if (getPos().x + 32 > o.getPos().x && getPos().x<o.getPos().x + o.getCurrentFrame().w && mPosY + 32 >o.getPos().y && mPosY < o.getPos().y + o.getCurrentFrame().h)
			{
				setVelocity(getVelocity().x , getVelocity().y* -1);
			}
		}
		
		
		
	}
}