#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "ball.h"
#include "Goal.h"
#include "object.h"
//#include "Utils.h"

RenderWindow window("GAMEEEEE 1.0", 640, 980);
bool init()
{
	//Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init has failed. Error :" << SDL_GetError() << std::endl;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialized!!!!! ERROR: " << Mix_GetError() << std::endl;
	}
	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf FAILEDDDD" << TTF_GetError() << std::endl;
		return false;
	}

	//If everything initialized fine
	return true;
}
bool SDLInitEverything = init();




TTF_Font* font = TTF_OpenFont("font/pixelfont2.ttf", 35);
SDL_Color color = { 255, 255, 255 };

SDL_Texture* ballTexture = window.loadTexture("animation/golfballbetterv1.png");
SDL_Texture* background = window.loadTexture("animation/bg.png");
SDL_Texture* goalTexture = window.loadTexture("animation/goal.png");
SDL_Texture* arrowTexture = window.loadTexture("animation/arrow.png");
SDL_Texture* obstacleTexture = window.loadTexture("animation/object.png");

Mix_Chunk* golfhit = Mix_LoadWAV("sfx/golfhit.wav");
Mix_Chunk* goalhit = Mix_LoadWAV("sfx/goalsound.wav");
Ball golf(Vector2(355, 800), ballTexture,arrowTexture);
Goal target(Vector2(355, 100), goalTexture);
//std::vector <Object> obstacles;
Object obstacle (Vector2(150,300), obstacleTexture);

//Entity entities[2] = {Entity(Vector2(50,100),ballTexture),Entity(Vector2(15,100),ballTexture) };

int stateMachine = 0;
bool gameRunning = true;
bool mousestate1 = false;
bool mousestate2 = false;
bool winner = false; 
double deltaTime = 0;
int level = 0;
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
					//if (!Mix_Playing(-1)) Mix_PlayChannel(-1, golfhit, 0);
				}
				break;
		}
		golf.updateGame( mousestate1, mousestate2, deltaTime, target, obstacle, golfhit, goalhit);
		if (golf.getWinState())
		{	
			stateMachine = 2;
			golf.setWinState(false);
			std::cerr << golf.getWinState();
		}
	
	
}
void intro()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				stateMachine = 1;
			}
			break;
		}
	}
	window.renderword("WELCOME WELCOME: WONDERLAND", font, color, 0, 0);
	window.display();
}
void outtro() {
	window.clear();
	
	window.renderword("GAME OVER", font, color, 220, 480);
	window.display();
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{	
				stateMachine = 1;
				std::cerr << "THIS WAS CLICKED"<< stateMachine<<std::endl;
				golf.setScale(1, 1);
				golf.setPos(250, 600);
			}
			break;
		}
	}
}
void display()
{
		window.clear();
		window.render(0, 0, background);
		window.render(target);
		window.render(golf);
		window.render(obstacle);
		for (Entity& e : golf.getArrow())
		{
			window.render(e);
		}

		//window.render(arrow);
		window.renderword("SHOTS LIMIT: YAY ", font, color,100,100);
		window.display();
}
void gameLoad()
{
	if (stateMachine == 0)
	{
		intro();

	}
	else if(stateMachine==1) {
		update();
		display();

	}
	else if (stateMachine == 2)
	{
		outtro();

	}
}



int main(int argc, char* args[])
{	
	
	while (gameRunning)
	{
		gameLoad();
	}
	TTF_CloseFont(font);
	window.cleanUp();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}