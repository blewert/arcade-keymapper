#pragma once

#include <iostream>
#include "SDL.h"
#include "window.h"

namespace keymapper
{
	class Mapper
	{
	public:
		void __fastcall OnThreadIteration(Window* window);
		void SetTimeoutSeconds(int seconds);
		void SetWarningSeconds(int seconds);

	private:
		int lastKeyPressed = 0;
		int warningTicks = 1000 * 10;
		int timeoutTicks = 1000 * 30;
		bool waitingForUserStart = true;

	};
}