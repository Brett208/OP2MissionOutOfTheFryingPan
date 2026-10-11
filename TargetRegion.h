#pragma once

#include "OP2Helper/OP2Helper.h"
#include <vector>


struct TargetRegion
{
	MAP_RECT area = MAP_RECT(LOCATION(0, 0), LOCATION(0, 0));
	std::vector<LOCATION> waypoints = { LOCATION(0, 0) };
};