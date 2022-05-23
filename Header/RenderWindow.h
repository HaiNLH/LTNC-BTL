#pragma once
#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Entity.h"

class RenderWindow
{
public:

	RenderWindow();
	SDL_Texture* loadTexture(const char* p_filePath);
	SDL_Renderer* getRender()
	{
		return renderer;
	}
	SDL_Window* getWindow()
	{
		return window;
	}
	void cleanUp();
	void clear();
	void rendercircle(Entity& p_entity);
	void render(Entity& p_entity);
	void render(int p_x, int p_y, SDL_Texture* p_tex);
	void renderword(const char* p_text, TTF_Font* font, SDL_Color textColor, int p_x, int p_y);
	//void render(SDL_Texture* p_tex);
	void display();

protected:
	SDL_Window* window;
	SDL_Renderer* renderer;

};


#endif