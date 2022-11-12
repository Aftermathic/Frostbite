#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity {
public:
	Entity(float p_x, float p_y, int p_w, int p_h, SDL_Texture* p_tex);

	float getX();
	float getY();
	int getW();
	int getH();

	void setX(float p_x);
	void setY(float p_y);

	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
private:
	float x, y;
	int w, h;

	SDL_Rect currentFrame;
	SDL_Texture* tex;
};