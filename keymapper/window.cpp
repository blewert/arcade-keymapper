#include "window.h"

keymapper::Window::Window(void)
{
	//Create the window
	this->window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, NULL);
	
	//Create the renderer
	this->CreateRenderer();
}

keymapper::Window::Window(unsigned int width = DEFAULT_WINDOW_WIDTH, unsigned int height = DEFAULT_WINDOW_HEIGHT) 
	: window_height(height), window_width(width)
{
	//Create the window
	this->window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, NULL);
	
	//Create the renderer
	this->CreateRenderer();
}

void keymapper::Window::RenderSplashScreen(const char* path) const
{
	//Load in the image, convert to a texture
	SDL_Surface* image = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, image);

	//Width and height
	int w, h;

	//Find the height and width of this texture
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	//Set the window size to this
	SDL_SetWindowSize(this->window, w, h);

	//Copy this into window pane
	SDL_RenderCopy(this->renderer, texture, NULL, NULL);

	//Present it 
	SDL_RenderPresent(this->renderer);

	//Free the surface
	SDL_FreeSurface(image);
}

void keymapper::Window::CreateRenderer(void)
{
	//Set to borderless
	SDL_SetWindowBordered(this->window, SDL_FALSE);

	//Create a new renderer
	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//Set up renderer hints
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

	//Clear once
	SDL_RenderClear(this->renderer);
	SDL_RenderPresent(this->renderer);
}