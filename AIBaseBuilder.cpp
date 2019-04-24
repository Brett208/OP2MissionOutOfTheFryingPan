#include "AIBaseBuilder.h"
#include "AIHelper.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"

void BuildAIBase(PlayerNum  aiPlayerNum, const LOCATION& initBaseLoc)
{
	LOCATION currentLoc = initBaseLoc;
	LOCATION vechStartLoc(initBaseLoc.x + 4, initBaseLoc.y + 4);
	MAP_RECT miningIdleRect(initBaseLoc.x - 4, initBaseLoc.y, initBaseLoc.x + 6, initBaseLoc.y + 4);
	Unit unit;
	

	CreateInitialAIUnit(unit, mapCommandCenter, initBaseLoc, aiPlayerNum, map_id::mapNone);//ComandCenter
	currentLoc.x = initBaseLoc.x + 5;
	CreateInitialAIUnit(unit, mapStructureFactory, currentLoc, aiPlayerNum, map_id::mapNone);
	currentLoc.x = initBaseLoc.x - 5;
	
	Unit commonSmelter;
	CreateInitialAIUnit(commonSmelter, mapCommonOreSmelter, currentLoc, aiPlayerNum, map_id::mapNone);
	currentLoc.y = initBaseLoc.y + 4;

	Unit commonMine;
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, currentLoc.x, currentLoc.y, BeaconTypes::OreTypeCommon, Yield::Bar2, Variant::Variant3);
	CreateInitialAIUnit(commonMine, mapCommonOreMine, currentLoc, aiPlayerNum, map_id::mapNone);

	currentLoc.x = initBaseLoc.x;
	currentLoc.y = initBaseLoc.y + 5;

	CreateInitialAIUnit(unit, mapVehicleFactory, currentLoc, aiPlayerNum, map_id::mapNone);
	currentLoc.y = initBaseLoc.y - 6;

	CreateInitialAIUnit(unit, mapTokamak, currentLoc, aiPlayerNum, map_id::mapNone);

	CreateTubeOrWallLine(initBaseLoc.x, initBaseLoc.y - 3, initBaseLoc.x, initBaseLoc.y - 1, mapTube);
	CreateTubeOrWallLine(initBaseLoc.x, initBaseLoc.y + 1, initBaseLoc.x, initBaseLoc.y + 5, mapTube);
	CreateTubeOrWallLine(initBaseLoc.x - 2, initBaseLoc.y, initBaseLoc.x - 1, initBaseLoc.y, mapTube);
	CreateTubeOrWallLine(initBaseLoc.x + 1, initBaseLoc.y, initBaseLoc.x + 3, initBaseLoc.y, mapTube);

	MiningGroup miningGroup;
	SetupMiningGroup(miningGroup, commonMine, commonSmelter, miningIdleRect, 3, aiPlayerNum);
	
}

void CreateInitialAIUnit(Unit unit, map_id unitType, LOCATION loc, PlayerNum aiPlayerNum, map_id Cargo)
{
	const UnitDirection rotation = UnitDirection::South;
	TethysGame::CreateUnit(unit, unitType, loc, aiPlayerNum, Cargo, rotation);
}