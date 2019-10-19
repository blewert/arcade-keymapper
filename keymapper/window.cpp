#include "mapper.h"

keymapper::Window::Window(void)
{
	//Call TTF init
	TTF_Init();

	//Create the window
	this->window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, NULL);
	
	//Create the renderer
	this->CreateRenderer();
}

void keymapper::Window::SetMapperInstance(keymapper::Mapper* mapper)
{
	//Just set the variable directly, this is a pointer and mapper
	//should be on the heap
	this->mapperInstance = mapper;
}

keymapper::Mapper* keymapper::Window::GetMapperInstance(void) const
{
	//Just return the mapper instance
	return this->mapperInstance;
}

void keymapper::Window::LoadMainFont(const char* path)
{
	//Open the font
	this->font = TTF_OpenFont(path, 24);
}


void keymapper::Window::LoadWarningImage(const char* path)
{
	//Load the surface
	SDL_Surface* surf = IMG_Load(path);

	//Make the warning image
	this->warningImage = SDL_CreateTextureFromSurface(this->renderer, surf);

	//And free the surface
	SDL_FreeSurface(surf);
}

void keymapper::Window::RenderText(const std::string& text, int x, int y, int align) const
{
	//Size the text's bounding box
	int w, h;
	TTF_SizeText(this->font, text.c_str(), &w, &h);

	//Build the rect for rendercopy 
	SDL_Rect rect = { x, y, w, h };

	//Centre alignment? Position accordingly
	if (align == ALIGN_CENTRE)
		rect = { x - w/2, y - h/2, w, h };

	//Build the surface, make a texture from it
	SDL_Surface* surf = TTF_RenderText_Blended(this->font, text.c_str(), { 255, 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surf);

	//Copy it into the window
	SDL_RenderCopy(this->renderer, texture, NULL, &rect);

	//Clean up
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
}

void keymapper::Window::Hide(void)
{
	//Hide the window
	SDL_HideWindow(this->window);
}

void keymapper::Window::RenderWarning(float diff) const
{
	//Get the window flags
	auto windowFlags = SDL_GetWindowFlags(this->window);

	//Is the window hidden? Show it!
	if (windowFlags & SDL_WINDOW_HIDDEN)
		SDL_ShowWindow(this->window);

	//Render the background
	SDL_RenderCopy(this->renderer, this->warningImage, NULL, NULL);

	//The string to render
	std::string str = std::to_string((int)ceil(diff)) + " seconds";

	//Where to render it
	int x = DEFAULT_WINDOW_WIDTH  / 2, 
		y = DEFAULT_WINDOW_HEIGHT / 2;

	//Refreshing page text
	this->RenderText("Refreshing page in:", x, y, ALIGN_CENTRE);

	//Render the countdown text
	this->RenderText(str, x, y + 50, ALIGN_CENTRE);	

	//Present it!
	SDL_RenderPresent(renderer);
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

	//Free the surface, destroy the texture
	SDL_FreeSurface(image);
	SDL_DestroyTexture(texture);
}

DWORD __stdcall keymapper::Window::JoypadThreadCallback(void* param)
{
	//Cast to an instance of Window*
	keymapper::Window* instance = (keymapper::Window*)param;

	//Get the instance of the mapper
	keymapper::Mapper* mapper = instance->GetMapperInstance();

	while (!instance->joypadThreadExited)
	{
		//Call onThreadIteration
		mapper->OnThreadIteration(instance);
	}

	std::cout << "exiting joypad detection thread" << std::endl;

	return 0;
}

void keymapper::Window::Close(void)
{
	//Set exited to true
	this->joypadThreadExited = true;

	//Close the window and renderer
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
}

void keymapper::Window::StartJoypadDetection(void)
{
	//Create the thread
	this->joypadThreadHandle = CreateThread(NULL, 0, this->JoypadThreadCallback, (void*)this, 0, &this->joypadThreadID);
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