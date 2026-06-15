#pragma once

#include "AIHelper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>

void SetAIIndex(PlayerNum playerNum);
void CreatePlymouthGuardPostCluster(LOCATION loc, std::vector<Unit>& buildings);
void RecordPlymouthGuardPostCluster(LOCATION loc, BuildingGroup& buildingGroup);