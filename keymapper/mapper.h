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

	};
}