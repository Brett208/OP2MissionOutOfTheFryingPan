#include "Environment.h"
#include "HFL/Source/HFL.h"


bool IsBlightInArea(MAP_RECT area)
{
	for (int x = area.x1; x <= area.x2; ++x)
	{
		for (int y = area.y1; y <= area.y2; ++y)
		{
			if (GameMapEx::GetTileEx(LOCATION(x, y)).microbe)
			{
				return true;
			}
		}
	}
	return false;
}
