#include "axismapper.h"

void AxisMapper::AddMap(char vkPositive, char vkNegative, float axisThreshold)
{
	//Build the struct
	AxisMapInfo infoStruct;
	
	//Set variables
	infoStruct.vkPositive = vkPositive;
	infoStruct.vkNegative = vkNegative;
	infoStruct.axisThreshold = axisThreshold;

	//Add into the map at this id
	this->axes.push_back(infoStruct);
}


void AxisMapper::Map(SDL_Event& event)
{
	//Figure out what axes is receiving motion
	//..

	//Figure out what axes is being pressed
	uint8_t axisID = event.jaxis.axis;

	//Get axis info from axis id
	AxisMapInfo& axisInfo = axes[axisID];

	//Use the axes data to get the character to press
	char vkCode = axisInfo.stepKey(event.jaxis.value);

	//Is this key already being held down? If so.. skip, we
	//want to hold when the axis value is negated or its
	//sgn changes
	if (vkCode == axisInfo.lastKeyDown)
		return;

	//Otherwise.. we need to do something: release all keys for this axis
	KeyUtil::SendKeyUp(axisInfo.vkNegative);
	KeyUtil::SendKeyUp(axisInfo.vkPositive);

	//If vkCode is 0, the axes has been reset to the centre.. we need to release last key
	if (vkCode)
	{
		//printf("[KEYDN] %2c, %3d, %3d, %3d%\n", vkCode, vkCode, 0, event.jaxis.value);
		KeyUtil::SendKeyDown(vkCode);
	}

	//Set the last key down to whatever
	axisInfo.lastKeyDown = vkCode;
}