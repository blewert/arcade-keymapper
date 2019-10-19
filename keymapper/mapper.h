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

		void StartChrome(void) const;
		void RefreshChrome(void) const;
		void RestartChrome(void) const;
		void CloseChrome(void) const;

	private:
		int lastKeyPressed = 0;
		int warningTicks = 1000 * 10;
		int timeoutTicks = 1000 * 30;
		bool waitingForUserStart = true;

	};
}