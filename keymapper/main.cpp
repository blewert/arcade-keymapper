#include "main.h"

void __cdecl InitialiseSDL()
{
	//Initialise SDL & subsystems
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	//Initialise relevant libraries
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	TTF_Init();

	//Initialise key util thing
	KeyUtil::Initialise();

	//Enable joypad events
	SDL_JoystickEventState(SDL_ENABLE);

	//Set up hints
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
}

int SDL_main(int argc, char* argv[])
{
	InitialiseSDL();

	//Show / hide the window depending on debug
	ShowWindow(GetConsoleWindow(), KEYMAPPER_DEBUG_STATUS);

	//Create a new window
	keymapper::Window* window = new keymapper::Window();

	//Create a new mapper, set the window's mapper instance
	keymapper::Mapper* mapper = new keymapper::Mapper();
	window->SetMapperInstance(mapper);

	//Load in assets
	window->LoadWarningImage("assets/img/background-2.jpg");
	window->LoadMainFont("assets/fonts/press-start.ttf");

	//Set up timeout values for automatic refresh (timeout)
	mapper->SetTimeoutSeconds(7);
	mapper->SetWarningSeconds(5);

	//Load config
	mapper->LoadConfigFile("assets/json/mapper_config.json");

	//Set up joypad mappings: player 1 & player 2
	mapper->AddJoyButtonMap(keymapper::JOYPAD_DEVICE_IDX_P1, "assets/json/p1_map.json");
	mapper->AddJoyAxisMap(keymapper::JOYPAD_DEVICE_IDX_P1, "assets/json/p1_map.json");
	//--
	mapper->AddJoyButtonMap(keymapper::JOYPAD_DEVICE_IDX_P2, "assets/json/p2_map.json");
	mapper->AddJoyAxisMap(keymapper::JOYPAD_DEVICE_IDX_P2, "assets/json/p2_map.json");

	//Find virtual indices and hide the window when done
	mapper->EnumerateJoypads(window);
	window->Hide();

	while (!window->joypadThreadExited)
	{
		//Call onThreadIteration
		mapper->OnThreadIteration(window);
	}

	//SDL_Delay(5000);
	window->Close();
	//SDL_Delay(3000);
	

    return 0;
}

