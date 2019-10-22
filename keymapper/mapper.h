#pragma once

#include <iostream>
#include "SDL.h"
#include "window.h"
#include <string>

namespace keymapper
{
	class Mapper
	{
	public:
		void __fastcall OnThreadIteration(Window* window);
		void SetTimeoutSeconds(int seconds);
		void SetWarningSeconds(int seconds);

		void StartProcess(const std::string& path) const;
		void CloseProcess(const wchar_t* name) const;
		void RefreshChrome(void) const;
		void RestartChrome(void) const;
		void TryEnumeration(void);

		void MapJoyInputDown(SDL_Event event);
		void MapJoyInputUp(SDL_Event event);

		bool waitingForVirtualEnumeration = true;

	private:
		int lastKeyPressed = 0;
		int warningTicks = 1000 * 5;
		int timeoutTicks = 1000 * 30;

		bool waitingForUserStart = true;

		int joypadVirtualIndexP1 = 0;

		std::string chromePath  = "\"C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe\"";
		std::string chromeFlags = "--chrome --kiosk http://games.researcharcade.com/ --incognito";
	};
}