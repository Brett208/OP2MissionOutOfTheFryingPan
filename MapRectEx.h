#pragma once

#include "OP2MissionSDK/Outpost2DLL/Outpost2DLL.h"
#include "OP2MissionSDK/HFL/Source/HFL.h"


namespace MapEx
{
	inline bool Check(const MAP_RECT& rect, LOCATION loc)
	{
		return const_cast<MAP_RECT&>(rect).Check(loc) != 0;
	}

	inline MAP_RECT GetFullRect()
	{
		return MAP_RECT(LOCATION(0, 0), LOCATION(GameMapEx::GetMapWidth(), GameMapEx::GetMapHeight()));
	}

	inline MAP_RECT GetRectCenteredOnLoc(const LOCATION& loc, int width, int height)
	{
		return MAP_RECT(loc.x - width / 2, loc.y - height / 2, loc.x + width / 2, loc.y + height / 2);
	}

	inline MAP_RECT GetRectCenteredOnLoc(const LOCATION& loc, int rectSize)
	{
		return GetRectCenteredOnLoc(loc, rectSize, rectSize);
	}
}
