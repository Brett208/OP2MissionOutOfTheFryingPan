#pragma once

#include "Outpost2DLL/Outpost2DLL.h"
#include <array>



void InitializePlayer(PlayerNum playerNumber, const LOCATION& initBaseLoc);
void CreateInitialUnit(Unit unit, map_id unitType, LOCATION loc, PlayerNum playerNumber, map_id Cargo);
void InitializePlayers(int humanPlayerCount);

