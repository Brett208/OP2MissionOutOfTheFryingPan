#pragma once
#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>

void BuildSouthAIBase(PlayerNum aiPlayerNum, LOCATION commandCenterLoc, LOCATION structureFactoryLoc);
void CreateMiddleGuardPostClusters(const LOCATION& center, std::vector<Unit>& southBuildings);
