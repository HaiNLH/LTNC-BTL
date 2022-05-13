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
#include "ui.h"
//#include "Utils.h"

RenderWindow window("GAMEEEEE 1.0", 640, 960);
bool init()
{
	//Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init has failed. Error :" << SDL_GetError() << std::endl;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

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

SDL_Texture* ballTexture = window.loadTexture("animation/golfballofficial.png");
SDL_Texture* background = window.loadTexture("animation/bg.png");
SDL_Texture* startTexture = window.loadTexture("animation/startbg.png");
SDL_Texture* goalTexture = window.loadTexture("animation/goal.png");
SDL_Texture* arrowTexture = window.loadTexture("animation/arrow.png");
SDL_Texture* obstacleTexture = window.loadTexture("animation/object.png");
SDL_Texture* obstacleTexture1 = window.loadTexture("animation/object32.png");
SDL_Texture* barTexture = window.loadTexture("animation/bar.png");
SDL_Texture* titleStart = window.loadTexture("animation/title.png");
SDL_Texture* uistartTexture = window.loadTexture("animation/uistart1.png");
SDL_Texture* uistartTexture1 = window.loadTexture("animation/uistart2.png");

Mix_Chunk* golfhit = Mix_LoadWAV("sfx/golfhit.wav");
Mix_Chunk* goalhit = Mix_LoadWAV("sfx/goalsound.wav");

//Mix_Music* introSFX = Mix_LoadMUS("sfx/intro.wav");
//std::vector <Object> obstacles;
#define MAX_LEVEL 2
int stateMachine = 0;
bool gameRunning = true;
bool mousestate1 = false;
bool mousestate2 = false;
bool winner = false; 
double deltaTime = 0;
int level = 1;
SDL_Event event;

ui hud(Vector2(254, 477), uistartTexture);
ui hud1(Vector2(254, 477), uistartTexture1);
Ball golf(Vector2(0, 0), ballTexture, arrowTexture);
Goal target(Vector2(0, 0), goalTexture);


std::vector<Object> loadMap(int level)
{
	std::vector <Object> tmp = {};
	switch (level)
	{
	case 1:
		tmp.push_back(Object(Vector2(32 *10 , 400), obstacleTexture1));
		tmp.push_back(Object(Vector2(32 * 10, 400), obstacleTexture1));
		tmp.push_back(Object(Vector2(32 * 11, 400), obstacleTexture1));
		tmp.push_back(Object(Vector2(32 * 12, 400), obstacleTexture1));
		tmp.push_back(Object(Vector2(32 * 13, 400), obstacleTexture1));
		tmp.push_back(Object(Vector2(32 * 14, 400), obstacleTexture1));
		tmp.push_back(Object(Vector2(32 * 15, 400), obstacleTexture1));
		tmp.push_back(Object(Vector2(32 * 16, 400), obstacleTexture1));
		tmp.push_back(Object(Vector2(32 * 17, 400), obstacleTexture1));
		tmp.push_back(Object(Vector2(32 * 18, 400), obstacleTexture1));
		tmp.push_back(Object(Vector2(32 * 19, 400), obstacleTexture1));
		tmp.push_back(Object(Vector2(0, 200), barTexture));
		tmp.push_back(Object(Vector2(0, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64 * 2, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64 * 3, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64 * 4, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64 * 5, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64 * 6, 480), obstacleTexture));
		
		break;
	case 2:
		tmp.push_back(Object(Vector2(0, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64 * 5, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64 * 6, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64 * 7, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64 * 8, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64 * 9, 480), obstacleTexture));
		break;
	}

	return tmp;
}
std::vector <Object> obstacle = loadMap(level);
bool inside(int x, int y)
{	
	if (x > hud.getPos().x && x<hud.getPos().x + hud.getCurrentFrame().w && y>hud.getPos().y && y < hud.getPos().y + hud.getCurrentFrame().h)
	{
		return true;
	}
	else return false;
}
void loadLevel(int level)
{	
	golf.setVelocity(0, 0);
	golf.setScale(1, 1);
	golf.setWinState(false);
	obstacle = loadMap(level);
	std::cerr << level << std::endl;
	switch (level)
	{
	case 1:
		golf.setPos(355,800);
		target.setPos(355,100);
		break;
	case 2:
		golf.setPos(100, 300);
		target.setPos(400, 800);
		break;
	}

}

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
				//mousestate1 = false;
				mousestate2 = false;
					
			}
			break;
		}
	golf.updateGame( mousestate1, mousestate2, deltaTime, target, obstacle, golfhit, goalhit);
	if (golf.getWinState()&&level>MAX_LEVEL)
	{	
			
		stateMachine = 2;
		//golf.setWinState(false);
		std::cerr << golf.getWinState();
			
	}
	if (golf.getScale().x<-0.5&&golf.getScale().y<-0.5)
	{	
		level++;	
		loadLevel(level);
	}
}
void intro()
{
	
	window.clear();
	window.render(0, 0, startTexture);
	
	//window.render(254, 477, uistartTexture);
	window.render(42, 240 - 100 - 50 + 4 * SDL_sin(SDL_GetTicks() * (3.14 / 1500)), titleStart);
	window.render(hud);

	//while (SDL_PollEvent(&event))
	if (SDL_PollEvent(&event) == 0) {}
	else if (event.type == SDL_QUIT)
	{
		gameRunning = false;
	}
		switch (event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_MOUSEMOTION:
		{
			//SDL_Rect* clips;
			
			if (inside(event.motion.x, event.motion.y))
			{
				SDL_WaitEvent(&event);
				std::cerr <<"YAY" << std::endl;
				window.render(hud1);
				
			}
			
						//clips = &hud.clip(inside);
						//window.uirender(hud, clips);
		}	
		break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT&& inside(event.motion.x, event.motion.y))
			{
				stateMachine = 1;
			}
			break;
		}
	//}
	
	window.display();

	
}
void outtro() {
	
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
				stateMachine = 0;
				golf.setScale(1, 1);
				level = 1;
				loadLevel(1);
			}
			break;
		}
	}
	window.clear();
	window.renderword("GAME OVER", font, color, 220, 480);
	window.display();
}
void display()
{
		window.clear();
		window.render(0, 0, background);
		window.render(target);
		window.render(golf);
		for (Object& o : obstacle)
		{
			window.render(o);
		}
		
		for (Entity& e : golf.getArrow())
		{
			window.rendercircle(e);
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
	
	loadLevel(level);
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