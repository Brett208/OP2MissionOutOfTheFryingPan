#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include "Environment.h"
#include "OffensiveStateManager.h"
#include "AIPlayer.h"

void OffensiveStateManager::Initialize(LOCATION northCommandCenterLoc, LOCATION southCommandCenterLoc, LOCATION northStructureFactoryLoc, LOCATION southStructureFactoryLoc)
{
	NorthCommandCenterLoc = northCommandCenterLoc;
	SouthCommandCenterLoc = southCommandCenterLoc;
	NorthStructureFactoryLoc = northStructureFactoryLoc;
	SouthStructureFactoryLoc = southStructureFactoryLoc;
}

void OffensiveStateManager::Update()
{
	if (hasLavaConsumedCenterRegion)
	{
		CheckRegionWestConsumed();
	}
	else if (hasBlightEnteredWestRegion)
	{
		CheckNorthBaseDestroyed();
		CheckSouthBaseDestroyed();
	}
	else
	{
		CheckRegionCenterConsumed();
	}
}

bool OffensiveStateManager::CheckCommandCenterDestroyed(LOCATION commandCenterLoc)
{
	PlayerBuildingEnum playerBuildingEnum = PlayerBuildingEnum(GetAIIndex(), mapCommandCenter);
	Unit unit;
	while (playerBuildingEnum.GetNext(unit))
	{
		if (unit.Location() == commandCenterLoc && unit.GetType() == mapCommandCenter)
		{
			return false;
		}
	}
	return true;
}

bool OffensiveStateManager::CheckStructureFactoryDestroyed(LOCATION structureFactoryLoc)
{
	PlayerBuildingEnum playerBuildingEnum = PlayerBuildingEnum(GetAIIndex(), mapStructureFactory);
	Unit unit;
	while (playerBuildingEnum.GetNext(unit))
	{
		if (unit.Location() == structureFactoryLoc && unit.GetType() == mapStructureFactory)
		{
			return false;
		}
	}
	return true;
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
	isNorthBaseDestroyed = CheckCommandCenterDestroyed(NorthCommandCenterLoc) && CheckStructureFactoryDestroyed(NorthStructureFactoryLoc);
}

void OffensiveStateManager::CheckSouthBaseDestroyed()
{
	isSouthBaseDestroyed = CheckCommandCenterDestroyed(SouthCommandCenterLoc) && CheckStructureFactoryDestroyed(SouthStructureFactoryLoc);
}
