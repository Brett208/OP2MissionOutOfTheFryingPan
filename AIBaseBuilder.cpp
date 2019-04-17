#include "AIBaseBuilder.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"

void BuildAIBase(PlayerNum  aiPlayerNum, const LOCATION& initBaseLoc)
{
	LOCATION currentLoc = initBaseLoc;
	LOCATION vechStartLoc(initBaseLoc.x + 4, initBaseLoc.y + 4);
	Unit unit;

	CreateInitialAIUnit(unit, mapCommandCenter, initBaseLoc, aiPlayerNum, map_id::mapNone); //ComandCenter
}

void CreateInitialAIUnit(Unit unit, map_id unitType, LOCATION loc, PlayerNum playerNumber, map_id Cargo)
{
	const UnitDirection rotation = UnitDirection::South;
	TethysGame::CreateUnit(unit, unitType, loc, playerNumber, Cargo, rotation);
}