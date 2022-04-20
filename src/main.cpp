#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "ball.h"
#include "Goal.h"
//#include "Utils.h"




RenderWindow window("GAMEEEEE 1.0", 720, 1080);

SDL_Texture* ballTexture = window.loadTexture("animation/golfballbetterv1.png");
SDL_Texture* background = window.loadTexture("animation/bg.png");
SDL_Texture* goalTexture = window.loadTexture("animation/goal.png");


Ball golf(Vector2(355, 800), ballTexture);
Goal target(Vector2(355, 100), goalTexture);
//Entity entities[2] = {Entity(Vector2(50,100),ballTexture),Entity(Vector2(15,100),ballTexture) };

TTF_Font* menufont = TTF_OpenFont("font/arial.ttf", 24);
SDL_Color white = { 255,255,255 }; 



bool gameRunning = true;
bool mousestate1 = false;
bool mousestate2 = false;
double deltaTime = 0;

SDL_Event event;

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;


void update()
{
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());
	//std::cerr << deltaTime << std::endl;
	//deltaTime=0.222;
	mousestate1 = false;
	//if (menufont == NULL) {
		//std::cerr << "FAILED SOMEWHERE I DONT KNOW XDDDD: " << TTF_GetError()<<std::endl;
	//}
	//while (SDL_PollEvent(&event))
	
		if (SDL_PollEvent(&event) == 0) {}
		else if (event.type == SDL_QUIT) 
		{
			gameRunning = false;
		}
			
		switch (event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				
				{
					mousestate1 = true;
					mousestate2 = true;
					
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					mousestate1 = false;
					mousestate2 = false;
				}
				break;
		}
		golf.updateGame(mousestate1, mousestate2, deltaTime, target);
	
	
}
void display()
{
	window.clear();
	window.render(0,0,background);
	window.render(target);
	window.render(golf);
	//window.renderMid(100, 100, menufont, white, "HELLO WORLD");
	window.display();
}



int main(int argc, char* args[])
{

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY SDLLLLLLLL_INIT HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init has failed. Error :" << SDL_GetError() << std::endl;
	if (!(TTF_Init()))
		std::cout << "TTF_Init has failed. ERROR :" << SDL_GetError() << std::endl;
	while (gameRunning)
	{
		update();
		display();
	}
	window.cleanUp();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}