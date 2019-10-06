#pragma once
#include "SDL.h"
#include "SDL_image.h"

namespace keymapper
{
	class Window
	{

	public:

		const static int DEFAULT_WINDOW_WIDTH = 800;
		const static int DEFAULT_WINDOW_HEIGHT = 600;

		Window(void);
		Window(unsigned int width, unsigned int height);

		void RenderSplashScreen(const char* path) const;


	private:
		SDL_Window * window = NULL;
		SDL_Renderer* renderer = NULL;

		unsigned int window_width = DEFAULT_WINDOW_WIDTH;
		unsigned int window_height = DEFAULT_WINDOW_HEIGHT;

		void CreateRenderer(void);
	};
}