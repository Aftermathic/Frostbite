#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Entity::Entity(float p_x, float p_y, int p_w, int p_h, SDL_Texture* p_tex)
:x(p_x), y(p_y), w(p_w), h(p_h), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = w;
	currentFrame.h = h;
}

float Entity::getX() {
	return x;
}

float Entity::getY() {
	return y;
}

int Entity::getW() {
	return w;
}

int Entity::getH() {
	return h;
}

void Entity::setX(float p_x) {
	x = p_x;
}

void Entity::setY(float p_y) {
	y = p_y;
}

SDL_Texture* Entity::getTex() {
	return tex;
}

SDL_Rect Entity::getCurrentFrame() {
	return currentFrame;
}
