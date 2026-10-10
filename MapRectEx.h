#pragma once

#include "OP2MissionSDK/Outpost2DLL/Outpost2DLL.h"
#include "OP2MissionSDK/HFL/Source/HFL.h"


inline bool CheckEx(const MAP_RECT& rect, LOCATION loc)
{
	return const_cast<MAP_RECT&>(rect).Check(loc) != 0;
}

inline MAP_RECT GetFullMapRect()
{
	return MAP_RECT(LOCATION(0, 0), LOCATION(GameMapEx::GetMapWidth(), GameMapEx::GetMapHeight()));
}
