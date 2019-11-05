#pragma once

#include <map>
#include <vector>

#include "SDL.h"

#include "keyutil.h"

class AxisMapper
{
public:
	void AddMap(char vkPositive, char vkNegative, float axisThreshold, float scale);
	void Map(SDL_Event& event);

	typedef struct AxisMapInfo
	{
		char lastKeyDown = '\0';
		char vkPositive, vkNegative;
		float axisThreshold;
		float scale;

		template <typename T> int sgn(T val)
		{
			return (T(0) < val) - (val < T(0));
		}

		template <typename T> int step(T val)
		{
			return (abs(val) > this->axisThreshold) ? (sgn(val)) : (0);
		}

		template <typename T> char stepKey(T val)
		{
			if (step(val) < 0)
				return vkNegative;

			else if (step(val) > 0)
				return vkPositive;

			else
				return 0;
		}

	} AxisMapInfo;

private:
	std::vector<AxisMapInfo> axes;

};
