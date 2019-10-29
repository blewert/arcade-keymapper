#include "keyutil.h"

INPUT KeyUtil::ip;

void KeyUtil::Initialise(void)
{
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
}

void KeyUtil::SendKeyPress(char key)
{
	//Just send down/up
	KeyUtil::SendKeyDown(key);
	KeyUtil::SendKeyUp(key);
}

void KeyUtil::SendKeyDown(char key)
{
	//Convert to WORD
	WORD vkCode = (WORD)key;

	//Set flags for key down
	ip.ki.dwFlags = 0;
	ip.ki.wVk = vkCode;

	//Send it
	SendInput(1, &ip, sizeof(INPUT));
}

void KeyUtil::SendKeyUp(char key)
{
	//Convert to WORD
	WORD vkCode = (WORD)key;

	//Send flags for key up
	ip.ki.wVk = vkCode;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;

	//Send it 
	SendInput(1, &ip, sizeof(INPUT));
}