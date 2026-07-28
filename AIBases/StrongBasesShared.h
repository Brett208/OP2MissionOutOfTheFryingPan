#pragma once

#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>

void SetupDefensiveFightGroups(PlayerNum aiPlayerNum, const std::vector<Unit> vehicleFactories, 
	MAP_RECT perimeterRect, MAP_RECT interiorRect);
