#pragma once
#ifndef GAMEMENU_H
#define GAMEMENU_H
#include <iostream>
#include <vector>
#include <SDL.h>

#include "Entity.h"

class Menu :public Entity {
public:
	Menu(Vector2 p_pos, SDL_Texture* p_tex);
	
private:

};

#endif