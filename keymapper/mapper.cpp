#include "mapper.h"

void __fastcall keymapper::Mapper::OnThreadIteration(keymapper::Window* window)
{
	//Get the event
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		//Escape pressed? rip in peace
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			window->Close();
	}
}