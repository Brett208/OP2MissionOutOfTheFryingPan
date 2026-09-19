#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include "Environment.h"
#include "OffensiveStateManager.h"

void OffensiveStateManager::Update()
{
	CheckRegionCenterConsumed();
	if (hasLavaConsumedCenterRegion)
	{
		CheckRegionWestConsumed();
	}
	else if (hasBlightEnteredWestRegion)
	{
		CheckNorthBaseDestroyed();
		CheckSouthBaseDestroyed();
	}
}

void OffensiveStateManager::CheckRegionCenterConsumed()
{
	if (!hasLavaConsumedCenterRegion && IsLavaInArea(MAP_RECT(147 + X_, 119 + Y_, 174 + X_, 134 + Y_)))
	{
		hasLavaConsumedCenterRegion = true;
	}
}

void OffensiveStateManager::CheckRegionWestConsumed()
{
	if (!hasBlightEnteredWestRegion && IsBlightInArea(MAP_RECT(86 + X_, 98 + Y_, 86 + X_, 131 + Y_)))
	{
		hasBlightEnteredWestRegion = true;
	}
}

void OffensiveStateManager::CheckNorthBaseDestroyed()
{

}

void OffensiveStateManager::CheckSouthBaseDestroyed()
{

}