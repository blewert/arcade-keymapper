#pragma once

#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

namespace keymapper
{
	class Mapper;

	class Window
	{

	public:

		const static int ALIGN_LEFT   = 0;
		const static int ALIGN_CENTRE = 1;

		const static int DEFAULT_WINDOW_WIDTH = 800;
		const static int DEFAULT_WINDOW_HEIGHT = 600;

		Window(void);
		Window(unsigned int width, unsigned int height);

		void Hide(void);
		void RenderText(const std::string& text, int x, int y, int align = ALIGN_LEFT, int color = 0xffffff) const;
		void LoadWarningImage(const char* path);
		void LoadMainFont(const char* path);
		void RenderSplashScreen(const char* path) const;
		void RenderWarning(float diff) const;
		void StartJoypadDetection(void);
		void Close(void);
		void SetMapperInstance(Mapper* mapper);
		Mapper* GetMapperInstance(void) const;

		bool joypadThreadExited = false;


	private:

		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;
		HANDLE joypadThreadHandle = NULL;
		DWORD joypadThreadID = 0;
		SDL_Texture* warningImage = NULL;
		TTF_Font* font = NULL;
		Mapper* mapperInstance = NULL;

		unsigned int window_width = DEFAULT_WINDOW_WIDTH;
		unsigned int window_height = DEFAULT_WINDOW_HEIGHT;

		void CreateRenderer(void);
		SDL_Color RGB24ToSDLColor(const int color) const;

		static DWORD __stdcall JoypadThreadCallback(void* param);
	};
}