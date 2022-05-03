#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "Entity.h"
#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
	{
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	}
	return texture;
}


void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}
void RenderWindow::clear()                                                               
{
	SDL_RenderClear(renderer);
}
//Render entity 
void RenderWindow::render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x;
	dst.y = p_entity.getPos().y;
	dst.w = p_entity.getCurrentFrame().w;
	dst.h = p_entity.getCurrentFrame().h;
	SDL_Point center = {dst.w/2,48 };
	SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst,p_entity.getAngle(),&center, SDL_FLIP_NONE);
}
void RenderWindow::render(int p_x, int p_y, SDL_Texture* p_tex)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w;
	src.h;
	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);
	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = src.w;
	dst.h = src.h;
	
	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}
void RenderWindow::renderCenter(const char* p_text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* surface = TTF_RenderText_Blended(font,
		p_text, textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 100, 100, texW, texH };
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);

}
/*void RenderWindow::renderMid(int p_x, int p_y, TTF_Font* font, SDL_Color color, const char* text)
{	

	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (surface == NULL) {
		std::cerr << "FAILED TO GET SURFACE!!!" << SDL_GetError() << std::endl;
	}
	
	SDL_Rect src;
	src.x = 0;
	src.y = 0; 
	src.w = 32;
	src.h = 32;
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = src.w;
	dst.h = src.h;
	SDL_RenderCopy(renderer, texture, &src, &dst);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}*/


void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}