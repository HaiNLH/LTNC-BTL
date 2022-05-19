#include <iostream>
#include <vector>
#include <string>
#include <fstream>
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
#include "gamemenu.h"
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
SDL_Texture* uihelpTexture1 = window.loadTexture("animation/uihelp1.png");
SDL_Texture* uihelpTexture2 = window.loadTexture("animation/uihelp2.png");
SDL_Texture* overlay = window.loadTexture("animation/overlay.png");
SDL_Texture* notcontinue = window.loadTexture("animation/continuenot.png");
SDL_Texture* continue1 = window.loadTexture("animation/continue1.png");
SDL_Texture* continue2 = window.loadTexture("animation/continue2.png");
SDL_Texture* soundTexture = window.loadTexture("animation/sound.png");
SDL_Texture* soundTexture1 = window.loadTexture("animation/sound1.png");
SDL_Texture* soundTexture2 = window.loadTexture("animation/sound2.png");
SDL_Texture* menuBG = window.loadTexture("animation/menuBG.png");
SDL_Texture* homeButton = window.loadTexture("animation/homeButton.png");
SDL_Texture* homeButton1 = window.loadTexture("animation/homeButton1.png");
SDL_Texture* restartButton = window.loadTexture("animation/restartButton.png");
SDL_Texture* restartButton1 = window.loadTexture("animation/restartButton1.png");
SDL_Texture* endscreen = window.loadTexture("animation/endscreen.png");
SDL_Texture* guide = window.loadTexture("animation/guide.png");
SDL_Texture* river = window.loadTexture("animation/river.png");


Mix_Chunk* golfhit = Mix_LoadWAV("sfx/golfhit.wav");
Mix_Chunk* goalhit = Mix_LoadWAV("sfx/goalsound.wav");
Mix_Chunk* gameMusic = Mix_LoadWAV("sfx/gameMusic.wav");
Mix_Chunk* buttonPressed = Mix_LoadWAV("sfx/buttonPressed.wav");
Mix_Chunk* watersound = Mix_LoadWAV("sfx/watersound.wav");

Mix_Music* introSFX = Mix_LoadMUS("sfx/intro.mp3");
Mix_Music* gameSFX = Mix_LoadMUS("sfx/gameSFX.mp3");
//std::vector <Object> obstacles;
#define MAX_LEVEL 4
float stateMachine = 0;
int minorState = 0;
bool gameRunning = true;
bool mousestate1 = false;
bool mousestate2 = false;
bool winner = false; 
bool savegame = true;
double deltaTime = 0;
int level = 1;
int menuState = 0;
bool newgame = true;
SDL_Event event;

ui sound[3] = { ui(Vector2(0,900),soundTexture), ui(Vector2(0,905),soundTexture1), ui(Vector2(0,905),soundTexture2)};
ui p_continue[3] = { ui(Vector2(254,587),notcontinue),ui(Vector2(254,577),continue1),ui(Vector2(254,587),continue2) };
ui help[2] = { ui(Vector2(254,677),uihelpTexture1),ui(Vector2(254,687),uihelpTexture2) };
ui hud[2] = { ui(Vector2(254,477),uistartTexture),ui(Vector2(254,487),uistartTexture1) };

Ball golf(Vector2(0, 0), ballTexture, arrowTexture);
Goal target(Vector2(0, 0), goalTexture);
Menu MenuBackground(Vector2(0,0),menuBG);
Menu button[4] = { Menu(Vector2(204,396),homeButton),Menu(Vector2(204,403),homeButton1),Menu(Vector2(304,396),restartButton),Menu(Vector2(304,403),restartButton1) };
ui soundMenu[3] = { ui(Vector2(404,396),soundTexture), ui(Vector2(404,403),soundTexture1), ui(Vector2(404,403),soundTexture2) };

std::vector <water> loadWater(int level)
{
	std::vector <water> temp = {};
	switch (level)
	{
	case 1:
		temp.push_back(water(Vector2(0, 300), river));
		temp.push_back(water(Vector2(128, 300), river));
		temp.push_back(water(Vector2(384, 300), river));
		temp.push_back(water(Vector2(512, 300), river));
		break;
		
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
		
	}
	return temp;
}
std::vector<water> water2 = loadWater(level);
std::vector<Object> loadMap(int level)
{
	std::vector <Object> tmp = {};
	switch (level)
	{
	case 1:

		break;
	case 2:
		tmp.push_back(Object(Vector2(320, 64 * 2), obstacleTexture));
		tmp.push_back(Object(Vector2(320, 64 * 3), obstacleTexture));
		tmp.push_back(Object(Vector2(320, 64 * 4), obstacleTexture));
		tmp.push_back(Object(Vector2(320, 64 * 5), obstacleTexture));
		tmp.push_back(Object(Vector2(320, 64 * 6), obstacleTexture));
		tmp.push_back(Object(Vector2(320, 64 * 7), obstacleTexture));
		tmp.push_back(Object(Vector2(320, 64 * 8), obstacleTexture));
		break;
	case 3:
		tmp.push_back(Object(Vector2(32 * 10, 400), obstacleTexture1));
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
		tmp.push_back(Object(Vector2(0, 300), barTexture));
		tmp.push_back(Object(Vector2(160, 300), barTexture));
		tmp.push_back(Object(Vector2(480, 200), barTexture));
		tmp.push_back(Object(Vector2(0, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64 * 2, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64 * 3, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64 * 4, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64 * 5, 480), obstacleTexture));
		tmp.push_back(Object(Vector2(64 * 6, 480), obstacleTexture));
		break;
	case 4:

		tmp.push_back(Object(Vector2(320, 64 * 2), obstacleTexture));
		tmp.push_back(Object(Vector2(320, 64 * 3), obstacleTexture));
		tmp.push_back(Object(Vector2(320, 64 * 4), obstacleTexture));
		tmp.push_back(Object(Vector2(320, 64 * 5), obstacleTexture));
		tmp.push_back(Object(Vector2(320, 64 * 6), obstacleTexture));
		tmp.push_back(Object(Vector2(320, 64 * 7), obstacleTexture));
		tmp.push_back(Object(Vector2(320, 64 * 8), obstacleTexture));
		tmp.push_back(Object(Vector2(0, 300), barTexture));
		tmp.push_back(Object(Vector2(160, 400), barTexture));
		tmp.push_back(Object(Vector2(384, 400), barTexture));
		tmp.push_back(Object(Vector2(480, 200), barTexture));
		break;
	}
	return tmp;
}
std::vector <Object> obstacle = loadMap(level);
bool inside(int x, int y, int mPosx, int mPosy, int w , int h)
{
	if (x > mPosx && x<mPosx + w && y>mPosy && y < mPosy + h)
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
	water2 = loadWater(level);
	std::cerr << level << std::endl;
	switch (level)
	{
	case 1:
		golf.setPos(320, 800);
		target.setPos(320, 100);
		break;
	case 2:
		golf.setPos(330, 80);
		target.setPos(320, 800);
		break;

	case 3:
		golf.setPos(320, 800);
		target.setPos(320, 100);
		break;
	case 4:
		golf.setPos(330, 80);
		target.setPos(320, 800);
		break;

	}

}
void save_game()
{
	std::ofstream save("game_save");

	save << golf.getPos().x;
	save << " ";
	save << golf.getPos().y;
	save << "\n";
	save << level;
	save << " ";
	save << golf.getSwings();
	save.close();
}

void load_files()
{
	std::ifstream load("game_save"); 
		if (load)
		{
			float mPosx, mPosy;
			int tmplevel;
			int shot;
			load >> mPosx;
			load >> mPosy;
			
			load.ignore();
			load >> tmplevel;
			load >> shot;
			golf.setSwing(shot);
			level = tmplevel;
			loadLevel(level);
			
			golf.setPos(mPosx, mPosy);
			load.close();
		}


}
void displayMenu()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	

	SDL_Event event;
	
	if (SDL_PollEvent(&event) == 0) {}
	else if (event.type == SDL_QUIT)
	{
		gameRunning = false;
	}

	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		if (inside(x, y, button[0].getPos().x, button[0].getPos().y, button[0].getCurrentFrame().w, button[0].getCurrentFrame().h))
		{	
			save_game();
			savegame = true;
			Mix_PlayChannel(-1, buttonPressed, 0);
			stateMachine = 0;
			menuState = 0;
			
		}
		else if (inside(x, y, button[2].getPos().x, button[2].getPos().y, button[2].getCurrentFrame().w, button[2].getCurrentFrame().h))
		{
			Mix_PlayChannel(-1, buttonPressed, 0);
			menuState = 0;
			golf.setScale(1, 1);
			level = 1;
			golf.setSwing(0);
			loadLevel(1);

		}
		else if (inside(event.motion.x, event.motion.y, soundMenu[0].getPos().x, soundMenu[0].getPos().y, soundMenu[0].getCurrentFrame().w, soundMenu[0].getCurrentFrame().h))
		{
			Mix_PlayChannel(-1, buttonPressed, 0);
			if (Mix_VolumeMusic(-1) > 0)
			{
				Mix_VolumeMusic(0);
			}
			else {
				Mix_VolumeMusic(128);
			}

		}
	}
		
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			menuState = 0;
	}

	
	window.render(MenuBackground);
	if ( inside(x, y, button[0].getPos().x, button[0].getPos().y, button[0].getCurrentFrame().w, button[0].getCurrentFrame().h)) window.render(button[1]);
	else window.render(button[0]);
	if (inside(x, y, button[2].getPos().x, button[2].getPos().y, button[2].getCurrentFrame().w, button[2].getCurrentFrame().h)) window.render(button[3]);
	else window.render(button[2]);
	if (inside(x, y, soundMenu[0].getPos().x, soundMenu[0].getPos().y, soundMenu[0].getCurrentFrame().w, soundMenu[0].getCurrentFrame().h) && Mix_VolumeMusic(-1) != 0)
	{
		window.render(soundMenu[1]);

	}
	else if (Mix_VolumeMusic(-1) != 0) window.render(soundMenu[0]);
	else if (Mix_VolumeMusic(-1) == 0)window.render(soundMenu[2]);

}

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
void update()
{
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());
	mousestate1 = false;
	
	if (SDL_PollEvent(&event) == 0) {}
	else if (event.type == SDL_QUIT) 
	{
		gameRunning = false;
	}
	if (menuState == 0)
	{
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
		case SDL_KEYDOWN:
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				menuState = 1;
		}
		break;
		}
	}
	
	golf.updateGame( mousestate1, mousestate2, deltaTime, target, obstacle,water2, golfhit, goalhit,  watersound);
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
void loadButton()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (inside(x, y, hud[0].getPos().x, hud[0].getPos().y, hud[0].getCurrentFrame().w, hud[0].getCurrentFrame().h))
		window.render(hud[1]);
	else window.render(hud[0]);

	if (inside(x, y, help[0].getPos().x, help[0].getPos().y, help[0].getCurrentFrame().w, help[0].getCurrentFrame().h)) {
		window.render(help[1]);
		window.render(30, 120, guide);
	}
	else window.render(help[0]);
	if (inside(x, y, sound[0].getPos().x, sound[0].getPos().y, sound[0].getCurrentFrame().w, sound[0].getCurrentFrame().h)&&Mix_VolumeMusic(-1)!=0)
	{
		window.render(sound[1]);

	}
	else if(Mix_VolumeMusic(-1) != 0) window.render(sound[0]);
	else if(Mix_VolumeMusic(-1) == 0)window.render(sound[2]);
	
	if(!savegame) window.render(p_continue[0]);
	else {
		if (inside(x, y, p_continue[1].getPos().x, p_continue[1].getPos().y, p_continue[1].getCurrentFrame().w, p_continue[1].getCurrentFrame().h)) window.render(p_continue[2]);
		else window.render(p_continue[1]);
	}

}
void intro()
{
	window.clear();
	window.render(0, 0, startTexture);
	window.render(42, 240 - 100 - 50 + 4 * SDL_sin(SDL_GetTicks() * (3.14 / 1500)), titleStart);
	//window.render(hud);

	//while (SDL_PollEvent(&event))
	if (SDL_PollEvent(&event) == 0) {}
	else if (event.type == SDL_QUIT)
	{
		gameRunning = false;
	}
	if (event.button.button == SDL_BUTTON_LEFT && inside(event.motion.x, event.motion.y, hud[0].getPos().x, hud[0].getPos().y, hud[0].getCurrentFrame().w, hud[0].getCurrentFrame().h))
	{
		golf.setScale(1, 1);
		level = 1;
		golf.setSwing(0);
		loadLevel(1);
		Mix_PlayChannel(-1, buttonPressed, 0);
		stateMachine = 1;
	}
	if (event.type== SDL_MOUSEBUTTONDOWN &&event.button.button == SDL_BUTTON_LEFT && inside(event.motion.x, event.motion.y, sound[0].getPos().x, sound[0].getPos().y, sound[0].getCurrentFrame().w, sound[0].getCurrentFrame().h))
	{	
		Mix_PlayChannel(-1, buttonPressed, 0);
		if (Mix_VolumeMusic(-1)>0)
		{
			Mix_VolumeMusic(0);
		}
		else {
			Mix_VolumeMusic(128);
		}
	}
	if (event.button.button == SDL_BUTTON_LEFT && inside(event.motion.x, event.motion.y, p_continue[1].getPos().x, p_continue[1].getPos().y, p_continue[1].getCurrentFrame().w, p_continue[1].getCurrentFrame().h)&&savegame)
	{
		Mix_PlayChannel(-1, buttonPressed, 0);
		load_files();
		//loadLevel(level);
		stateMachine = 1;
		
	}
	loadButton();
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
				golf.setSwing(0);
				savegame = false;
				loadLevel(1);
				
			}
			break;
		}
	}
	window.clear();
	window.render(0,0,endscreen);
	window.display();
}
void display()
{
		window.clear();
		window.render(0, 0, background);
		window.render(target);
		window.render(golf);
		for (water& w : water2)
		{
			window.render(w);
		}
		for (Object& o : obstacle)
		{
			window.render(o);
		}
		
		
		for (Entity& e : golf.getArrow())
		{
			window.rendercircle(e);
		}
		std::string swing = "SWINGS: " + std::to_string(golf.getSwings());
		std::string levelText = "LEVEL: " + std::to_string(level);
		
		window.render(0, 0, overlay);
		window.renderword(swing.c_str(), font, color, 140, 5);

		window.render(380, 0, overlay);
		window.renderword(levelText.c_str(), font, color, 505, 5);
		
		
		//window.display();
}
std::string input;

void getUserName()
{
	SDL_StartTextInput();
	static const unsigned char* keys = SDL_GetKeyboardState(NULL);

	SDL_Event e;


	// Clear the window to white

	window.render(0, 0, startTexture);
	window.renderword("ENTER YOUR NAME: ", font, color, 350,300);
	// Event loop
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
		case SDL_QUIT:
			gameRunning = false;
		case SDL_TEXTINPUT:
			input += e.text.text;
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_BACKSPACE && input.size()) {
				input.pop_back();
			}
			 if (e.key.keysym.sym == SDLK_KP_ENTER && input.size())
			{

				stateMachine = 3;
			}
			break;
		
		}
	}

	window.renderword(input.c_str(), font, color, 320, 380);
	window.display();

}
void gameLoad()
{
	if (stateMachine == 0)
	{	

		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(introSFX, -1);
		}
		intro(); 
	}
	else if(stateMachine==1) 
	{
		update();
		display();
		if (menuState == 1)
		{
			displayMenu();
		}
		window.display();
	}
	else if (stateMachine == 2)
	{
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
		}

		if (golf.getSwings() < 20)
		{
			getUserName();

		}
		else {
			stateMachine = 3;
		}

	}
	else if (stateMachine == 3)
	{
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
		}
		

		outtro();
	} 
}




int main(int argc, char* args[])
{	
	if (gameSFX == NULL)
	{
		std::cerr << "MUSIC FAILED" << Mix_GetError();

	}
	loadLevel(level);
	while (gameRunning)
	{
		gameLoad();
	}

	Mix_FreeMusic(introSFX);
	TTF_CloseFont(font);
	window.cleanUp();
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}