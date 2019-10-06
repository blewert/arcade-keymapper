#pragma once
#include <windows.h>
#include <iostream>
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
		void StartJoypadDetection(void);
		void Close(void);

		bool joypadThreadExited = false;


	private:

		SDL_Window * window = NULL;
		SDL_Renderer* renderer = NULL;
		HANDLE joypadThreadHandle = NULL;
		DWORD joypadThreadID = 0;

		unsigned int window_width = DEFAULT_WINDOW_WIDTH;
		unsigned int window_height = DEFAULT_WINDOW_HEIGHT;

		void CreateRenderer(void);

		static DWORD __stdcall JoypadThreadCallback(void* param);
	};
}