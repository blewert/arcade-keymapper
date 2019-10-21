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

void keymapper::Mapper::CloseProcess(const wchar_t* name) const
{
	// god bless stackoverflow
	// <https://stackoverflow.com/questions/865152/how-can-i-get-a-process-handle-by-its-name-in-c>
	//

	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	//----
	//Run through all processes and kill chrome
	//----

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			//wcsicmp, yikes what a name: wide compare strings with case insensitivity
			//..

			if (_wcsicmp(entry.szExeFile, name) == 0)
			{
				//Open that process
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

				//Terminate it
				TerminateProcess(hProcess, -1);

				//Close that process
				CloseHandle(hProcess);
			}
		}
	}

	CloseHandle(snapshot);
}

void keymapper::Mapper::StartProcess(const std::string& path) const
{
	//Startup info
	STARTUPINFOA info = { sizeof(info) };
	
	//Process info for startup
	PROCESS_INFORMATION processInfo;

	LPSTR str = const_cast<LPSTR>(path.c_str());

	std::cout << str << std::endl;

	if (CreateProcessA(NULL, str, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
	{
		//It's created it so detach from parent process
		//..

		WaitForSingleObject(processInfo.hProcess, INFINITE);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}
	else
	{
		DWORD error = GetLastError();
		std::cout << std::endl << error << std::endl;
	}
}

void keymapper::Mapper::RestartChrome(void) const
{
	//Close chrome
	//this->CloseProcess(L"chrome.exe");

	//Start chrome
	//this->StartProcess(chromePath + " " + chromeFlags);
}

void keymapper::Mapper::RefreshChrome(void) const
{
	HWND hwnd = NULL;

	while (true)
	{
		hwnd = FindWindowEx(0, hwnd, L"Chrome_WidgetWin_1", NULL);

		if (!hwnd)
			break;
		
		if (!IsWindowVisible(hwnd))
			continue;

		SetForegroundWindow(hwnd);

		INPUT ip;
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0;
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;
		ip.ki.dwFlags = 0;

		ip.ki.wVk = VK_CONTROL;
		SendInput(1, &ip, sizeof(INPUT));

		ip.ki.wVk = VK_F5;
		SendInput(1, &ip, sizeof(INPUT));

		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		ip.ki.wVk = VK_CONTROL;
		SendInput(1, &ip, sizeof(INPUT));

		ip.ki.wVk = VK_F5;
		SendInput(1, &ip, sizeof(INPUT));

		printf("woop");
	}

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

		if (SDL_TICKS_PASSED(SDL_GetTicks(), this->lastKeyPressed + this->timeoutTicks))
		{
			//They've passed the warning!
			//..

			//Hide the window
			window->Hide();

			//Refresh chrome, somehow
			this->RestartChrome();

			//Set waiting for user to true
			this->waitingForUserStart = true;
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

			else 
			{
				window->Hide();
			}
		}
	}
}