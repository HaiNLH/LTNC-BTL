#include "Entity.h"
#include <SDL.h>
#include <SDL_image.h>


Entity::Entity(Vector2 p_pos, SDL_Texture* p_tex)
	:pos(p_pos),tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
	SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);//this function will return the width and height of pointer texture!!!! problem solved each texture each size

}
void Entity::setPos(float x, float y) {
	pos.x = x;
	pos.y = y;
}
void Entity::setAngle(float p_angle)
{
	angle = p_angle;
}
void Entity::setScale(float x, float y)
{
	scale.x = x;
	scale.y = y;
}
SDL_Texture* Entity::getTex() {
	return tex;
}
SDL_Rect Entity::getCurrentFrame() {
	return currentFrame;
}