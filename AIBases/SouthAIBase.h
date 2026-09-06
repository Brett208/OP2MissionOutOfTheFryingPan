#pragma once
#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>

void BuildSouthAIBase(PlayerNum aiPlayerNum, const LOCATION& initBaseLoc);
void CreateMiddleGuardPostClusters(const LOCATION& center, std::vector<Unit>& southBuildings);
