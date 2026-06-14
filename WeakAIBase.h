#pragma once

#include "Outpost2DLL/Outpost2DLL.h"

extern bool weakBaseCanAttack;

void UpdateWeakAIBase();
void BuildAIBase(PlayerNum  aiPlayerNum, const LOCATION& initBaseLoc);
void RecordBuildings(BuildingGroup& buildingGroup);
