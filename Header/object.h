#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "Entity.h"
#include "Math.h"

class Object :public Entity
{
public:
	Object(Vector2 p_pos, SDL_Texture* p_tex);
private:

};