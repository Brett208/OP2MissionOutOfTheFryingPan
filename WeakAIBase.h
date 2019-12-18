#pragma once

#include "OffensiveFightGroup.h"
#include "Outpost2DLL/Outpost2DLL.h"

void UpdateWeakAIBase();
Export void AddTankWeakAIBase();
void BuildAIBase(PlayerNum  aiPlayerNum, const LOCATION& initBaseLoc);
void CreateInitialAIBuilding(Unit& unit, map_id unitType, LOCATION loc, PlayerNum playerNumber, map_id Cargo);
void createGuardPostCluster(PlayerNum aiPlayerNum, LOCATION loc);
void recordBuildings(BuildingGroup& buildingGroup);
