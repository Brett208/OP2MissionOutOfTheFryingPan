#pragma once

#include "OffensiveFightGroup.h"
#include "Outpost2DLL/Outpost2DLL.h"

void UpdateWeakAIBase();
void BuildAIBase(PlayerNum  aiPlayerNum, const LOCATION& initBaseLoc);
void CreateInitialAIBuilding(Unit& unit, map_id unitType, LOCATION loc, PlayerNum playerNumber, map_id Cargo);
