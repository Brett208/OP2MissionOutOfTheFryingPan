#pragma once

#include "OffensiveFightGroup.h"
#include "Outpost2DLL/Outpost2DLL.h"

void UpdateWeakAIBase();
Export void AddTankWeakAIBase();
void BuildAIBase(PlayerNum  aiPlayerNum, const LOCATION& initBaseLoc);
void createGuardPostCluster(PlayerNum aiPlayerNum, LOCATION loc);
void recordBuildings(BuildingGroup& buildingGroup);
