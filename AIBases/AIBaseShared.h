#pragma once

#include "../AIHelper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>

void SetAIIndex(PlayerNum playerNum);
void CreatePlymouthGuardPostCluster(LOCATION loc, std::vector<Unit>& buildings);
void RecordPlymouthGuardPostCluster(LOCATION loc, BuildingGroup& buildingGroup);

inline void RecordBuildingConst(BuildingGroup& buildingGroup, LOCATION buildingLocation, map_id unitType, map_id cargoOrWeapon)
{
	buildingGroup.RecordBuilding(buildingLocation, unitType, cargoOrWeapon);
}
