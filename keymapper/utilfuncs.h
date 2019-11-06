#pragma once

//C includes
#include <iostream>

//Define debug stuff
bool keymapperIsDebug = true;

int printd(const char* format, ...)
{
	//Not debugging? return false
	if (!keymapperIsDebug)
		return false;

	//Initialise the varargs list with format
	va_list args;
	va_start(args, format);

	//Call printf's long lost cousin; vprintf
	vprintf(format, args);

	//end
	va_end(args);
}