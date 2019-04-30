#pragma once

#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"

void BuildAIBase(PlayerNum  aiPlayerNum, const LOCATION& initBaseLoc);
void CreateInitialAIUnit(Unit& unit, map_id unitType, LOCATION loc, PlayerNum playerNumber, map_id Cargo);