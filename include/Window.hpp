#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Entity.hpp"

class Window {
	public:
		Window(const char* p_title, int p_w, int p_h);
		SDL_Texture* loadTexture(const char* p_filePath);

		void cleanUp();
		void clear();
		void render(Entity& p_entity);
		void display();

		void displayText(std::string text, int x, int y, TTF_Font *textFont, SDL_Color color);

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
};