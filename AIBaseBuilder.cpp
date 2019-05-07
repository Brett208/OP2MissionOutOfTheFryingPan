#include "AIBaseBuilder.h"
#include "AIHelper.h"
#include "AIPlayer.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"

void PopulateDefensiveFightGroup(PlayerNum aiPlayerNum);
void AddLynx(FightGroup& fightGroup, const LOCATION& loc, map_id weapon, PlayerNum playerNum);

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

	CreateTubeLine(initBaseLoc + LOCATION(0, -3), initBaseLoc + LOCATION(0, -1));
	CreateTubeLine(initBaseLoc + LOCATION(0, 1), initBaseLoc + LOCATION(0, 5));
	CreateTubeLine(initBaseLoc + LOCATION(-2, 0), initBaseLoc + LOCATION(-1, 0));
	CreateTubeLine(initBaseLoc + LOCATION(1, 0), initBaseLoc + LOCATION(3, 0));

	MiningGroup miningGroup;
	SetupMiningGroup(miningGroup, commonMine, commonSmelter, miningIdleRect, 3, aiPlayerNum);
	
	PopulateDefensiveFightGroup(aiPlayerNum);
}

void CreateInitialAIUnit(Unit& unit, map_id unitType, LOCATION loc, PlayerNum aiPlayerNum, map_id Cargo)
{
	const UnitDirection rotation = UnitDirection::South;
	TethysGame::CreateUnit(unit, unitType, loc, aiPlayerNum, Cargo, rotation);
}

void PopulateDefensiveFightGroup(PlayerNum aiPlayerNum)
{
	MAP_RECT guardedRect(68 + X_, 122 + Y_, 80 + X_, 140 + Y_);
	FightGroup fightGroup = CreateFightGroup(Player[aiPlayerNum]);
	fightGroup.AddGuardedRect(guardedRect);

	// 3 ESG, 3 EMP, 3 Sticky, 3 RPG, 3 Microwave
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapESG, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapESG, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapESG, aiPlayerNum);

	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapEMP, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapEMP, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapEMP, aiPlayerNum);

	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapStickyfoam, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapStickyfoam, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapStickyfoam, aiPlayerNum);

	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapRPG, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapRPG, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapRPG, aiPlayerNum);

	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapMicrowave, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapMicrowave, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapMicrowave, aiPlayerNum);

	
	int targetUnitCount = 5;

	switch (HumanPlayerCount())
	{
	case 3: {
		targetUnitCount = 8;
		break;
	}
	case 4: {
		targetUnitCount = 12;
		break;
	}
	}

	fightGroup.SetTargCount(map_id::mapLynx, map_id::mapESG, targetUnitCount);
	fightGroup.SetTargCount(map_id::mapLynx, map_id::mapRPG, targetUnitCount);
	fightGroup.SetTargCount(map_id::mapLynx, map_id::mapMicrowave, targetUnitCount);
	fightGroup.SetTargCount(map_id::mapLynx, map_id::mapStickyfoam, targetUnitCount);
	fightGroup.SetTargCount(map_id::mapLynx, map_id::mapEMP, targetUnitCount);

}

void AddLynx(FightGroup& fightGroup, const LOCATION& loc, map_id weapon, PlayerNum playerNum)
{
	int direction = TethysGame::GetRand(8);

	Unit unit;
	TethysGame::CreateUnit(unit, map_id::mapLynx, loc, playerNum, weapon, direction);
	unit.DoSetLights(true);
	fightGroup.TakeUnit(unit);
}
