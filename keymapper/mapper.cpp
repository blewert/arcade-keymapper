#include "mapper.h"

void keymapper::Mapper::SetTimeoutSeconds(int seconds)
{
	//Just set ticks to the amount of seconds times by 1000 (because this is in ms and we're doing s -> ms)
	this->timeoutTicks = seconds * 1000;
}

void keymapper::Mapper::SetWarningSeconds(int seconds)
{
	//Just set ticks to the amount of seconds times by 1000 (because this is in ms and we're doing s -> ms)
	this->warningTicks = seconds * 1000;
}

void __fastcall keymapper::Mapper::OnThreadIteration(keymapper::Window* window)
{
	//Get the event
	SDL_Event event;

	if (!this->waitingForUserStart)
	{
		//It's already been started by the user..
		//..

		if (SDL_TICKS_PASSED(SDL_GetTicks(), this->lastKeyPressed + this->timeoutTicks - this->warningTicks))
		{
			//Have they passed the last key press + timeout? If so.. we need to render a warning
			//..

			//Figure out how many seconds are left
			float diff = ((this->lastKeyPressed + this->timeoutTicks) - SDL_GetTicks()) / 1000.0f;

			//Render the warning
			window->RenderWarning(diff);
		}
	}

	while (SDL_PollEvent(&event))
	{
		//Escape pressed? rip in peace
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			window->Close();

		//Key pressed? Update key time
		if (event.type == SDL_KEYDOWN)
		{
			//Set last key press to current ticks
			this->lastKeyPressed = SDL_GetTicks();

			//Is waiting for user key press true? Set to false
			if (this->waitingForUserStart)
				this->waitingForUserStart = false;
		}
	}
}