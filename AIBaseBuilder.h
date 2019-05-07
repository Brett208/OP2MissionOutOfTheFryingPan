#pragma once

#include "Outpost2DLL/Outpost2DLL.h"

void BuildAIBase(PlayerNum  aiPlayerNum, const LOCATION& initBaseLoc);
void CreateInitialAIUnit(Unit& unit, map_id unitType, LOCATION loc, PlayerNum playerNumber, map_id Cargo);
