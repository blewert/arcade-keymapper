#include "main.h"

int SDL_main(int argc, char* argv[])
{
	//Create a new window
	keymapper::Window* window = new keymapper::Window();

	//Render the splash screen
	window->RenderSplashScreen("splash.jpg");


	SDL_Delay(3000);
	

    return 0;
}

