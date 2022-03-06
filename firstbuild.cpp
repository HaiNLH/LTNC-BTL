//using sdl and standard IO
#include <SDL.h>
#include <iostream>
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//STarts up SDL and creates window
bool init();

// Load media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to 
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen 
SDL_Surface* gHelloWorld = NULL;

int main(int argc, char* argsp[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}

	else
	{
		//load media 
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Aply the image
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

			//Updaate the surface 
			SDL_UpdateWindowSurface(gWindow);

			//wait 10 secs
			SDL_Delay(5000);
		}
	}
	//Free resources and close SDL
	close();
	return 0;

}
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//create Window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}
bool loadMedia()
{
	//Loading success flag;
	bool success = true;

	//Load splash image 
	gHelloWorld = SDL_LoadBMP("02_getting_an_image_on_the_screen/hello_world.bmp");
	if (gHelloWorld == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
		success = false;
	}
	return success;
}
void close()
{
	//Deal locate surface 
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//quit SDl subsystem
	SDL_Quit();
}