#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.h"


int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY SDLLLLLLLL_INIT HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init has failed. Error :" << SDL_GetError() << std::endl;
	RenderWindow window("GAMEEEEE 1.0", 720, 1080);

	SDL_Texture* ball = window.loadTexture("animation/golfballbetterv1.png");

	bool gameRunning = true;
	SDL_Event event;
	while (gameRunning)
	{
		//Get control and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}
		window.clear();
		window.render(ball);
		window.display();
	}
	window.cleanUp();
	SDL_Quit();
	return 0;
}