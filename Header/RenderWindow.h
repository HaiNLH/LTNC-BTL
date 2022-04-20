#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Entity.h"




class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	
	
	int getRefreshRate();
	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void render(int p_x, int p_y, SDL_Texture* p_tex);
	void renderMid(int p_x, int p_y, TTF_Font* font, SDL_Color color, const char* text);
	//void render(SDL_Texture* p_tex);
	void display();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

};