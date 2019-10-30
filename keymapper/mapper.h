#pragma once


#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

#include "json.hpp"
#include "SDL.h"

#include "window.h"
#include "keyutil.h"
#include "axismapper.h"


namespace keymapper
{
	using json = nlohmann::json;

	enum E_JOYPAD_DEVICE_IDX
	{
		JOYPAD_DEVICE_IDX_P1,
		JOYPAD_DEVICE_IDX_P2,
	};

	enum E_JOYPAD_BUTTON_IDX
	{
		JOYPAD_BUTTON_IDX_EXIT,
		JOYPAD_BUTTON_IDX_START,
		JOYPAD_BUTTON_IDX_A,
		JOYPAD_BUTTON_IDX_B,
		JOYPAD_BUTTON_IDX_C,
		JOYPAD_BUTTON_IDX_D,
		JOYPAD_BUTTON_IDX_E,
		JOYPAD_BUTTON_IDX_F
	};

	class Mapper
	{
	public:
		Mapper(void);

		void __fastcall OnThreadIteration(Window* window);
		void SetTimeoutSeconds(int seconds);
		void SetWarningSeconds(int seconds);

		void StartProcess(const std::string& path) const;
		void CloseProcess(const wchar_t* name) const;
		void RefreshChrome(void) const;
		void RestartChrome(void) const;
		void EnumerateJoypads(Window* window);

		void MapJoyInputDown(SDL_Event event);
		void MapJoyInputUp(SDL_Event event);
		void MapJoyAxisMotion(SDL_Event event);

		void AddJoyAxisMap(unsigned int joypadIndex, const char* file);
		void AddJoyButtonMap(unsigned int joypadIndex, const char* file);

		bool waitingForVirtualEnumeration = true;

	private:

		std::map<unsigned int, AxisMapper*> axisMap;
		std::map<unsigned int, unsigned int> enumerationMap;
		std::map<unsigned int, std::map<int, char>*> joypadMappings;

		int lastKeyPressed = 0;
		int warningTicks = 1000 * 5;
		int timeoutTicks = 1000 * 30;

		bool waitingForUserStart = true;

		std::string chromePath  = "\"C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe\"";
		std::string chromeFlags = "--chrome --kiosk http://games.researcharcade.com/ --incognito";
	};
}