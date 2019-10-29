#pragma once

#include <windows.h>

class KeyUtil
{
public:
	static void SendKeyDown(char key);
	static void SendKeyUp(char key);
	static void SendKeyPress(char key);
	static void Initialise(void);

private:
	static INPUT ip;
};

