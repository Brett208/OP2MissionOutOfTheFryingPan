#include "PlayerInitialization.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include<array>
#include<vector>

const std::array<LOCATION, 4> playerStartLocs{
	LOCATION(152 + X_, 110 + Y_),
	LOCATION(172 + X_, 110 + Y_),
	LOCATION(136 + X_, 44 + Y_),
	LOCATION(160 + X_, 133 + Y_),
};

const ResourceSet resourceSet{
	{
		// Kids, Adults, Scientist, Food, Common, Rare
		{ 27, 18, 22, 4000, 0, 0 },		// Easy
		{ 24, 15, 20, 3500, 0, 0 },		// Medium
		{ 20, 12, 18, 3000, 0, 0 },		// Hard
	}
};

void InitializePlayers(int humanPlayerCount)
{
	std::vector<LOCATION> initBaseLocs(playerStartLocs.size());
	std::copy(playerStartLocs.begin(), playerStartLocs.end(), initBaseLocs.begin());

	for (int i = 0; i < humanPlayerCount; ++i)
	{
		InitPlayerResources(i, resourceSet);

		const int locationIndex = TethysGame::GetRand(initBaseLocs.size());
		InitializePlayer(static_cast<PlayerNum>(i), initBaseLocs[locationIndex]);
		initBaseLocs.erase(initBaseLocs.begin() + locationIndex);

	}
}


void InitializePlayer(PlayerNum playerNumber, const LOCATION& initBaseLoc)
{

	LOCATION currentLoc = initBaseLoc;
	LOCATION vechStartLoc(initBaseLoc.x + 4, initBaseLoc.y + 4);
	Unit unit;

	CreateInitialUnit(unit, mapCommandCenter, initBaseLoc, playerNumber, map_id::mapNone); //ComandCenter
	currentLoc.y = initBaseLoc.y - 5;

	CreateInitialUnit(unit, mapBasicLab, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.y = initBaseLoc.y + 7;
	
	CreateInitialUnit(unit, mapCommonOreSmelter, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x = initBaseLoc.x - 5;
	currentLoc.y = initBaseLoc.y;

	CreateInitialUnit(unit, mapStructureFactory, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x = initBaseLoc.x + 5;
	
	CreateInitialUnit(unit, mapAgridome, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x = initBaseLoc.x + 10;
	currentLoc.y = initBaseLoc.y - 10;
	
	CreateInitialUnit(unit, mapTokamak, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x = initBaseLoc.x;
	currentLoc.y = initBaseLoc.y + 11;

	CreateTubeOrWallLine(initBaseLoc.x, initBaseLoc.y - 5, initBaseLoc.x, initBaseLoc.y + 7,mapTube);
	CreateTubeOrWallLine(initBaseLoc.x - 2, initBaseLoc.y, initBaseLoc.x + 4, initBaseLoc.y, mapTube);

	TethysGame::CreateBeacon(map_id::mapMiningBeacon, currentLoc.x, currentLoc.y, BeaconTypes::OreTypeCommon, Yield::Bar2, Variant::Variant3);
	currentLoc.x = vechStartLoc.x;
	currentLoc.y = vechStartLoc.y;

	CreateInitialUnit(unit, map_id::mapConVec, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x++;
	CreateInitialUnit(unit, map_id::mapConVec, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x++;
	CreateInitialUnit(unit, map_id::mapConVec, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x++;
	CreateInitialUnit(unit, map_id::mapConVec, currentLoc, playerNumber, map_id::mapNone);

	currentLoc.x = vechStartLoc.x;
	currentLoc.y++;

	CreateInitialUnit(unit, map_id::mapEarthworker, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x++;
	CreateInitialUnit(unit, map_id::mapCargoTruck, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x++;
	CreateInitialUnit(unit, map_id::mapCargoTruck, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x++;
	CreateInitialUnit(unit, map_id::mapCargoTruck, currentLoc, playerNumber, map_id::mapNone);

	currentLoc.x = vechStartLoc.x;
	currentLoc.y++;

	CreateInitialUnit(unit, map_id::mapRoboMiner, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x++;
	CreateInitialUnit(unit, map_id::mapRoboSurveyor, currentLoc, playerNumber, map_id::mapNone);

	
	map_id cargo = map_id::mapMicrowave;
	if (Player[playerNumber].IsEden()) {
		cargo = map_id::mapLaser;
	}

	for (int i = 0; i < TethysGame::InitialUnits(); ++i)
	{
		currentLoc.x = vechStartLoc.x + i % 4;
		currentLoc.y = vechStartLoc.y + 4 + i / 4;

		CreateInitialUnit(unit, map_id::mapLynx, currentLoc, playerNumber, cargo);
	}
}

void CreateInitialUnit(Unit unit, map_id unitType, LOCATION loc, PlayerNum playerNumber, map_id Cargo)
{
	const UnitDirection rotation = UnitDirection::South;
	TethysGame::CreateUnit(unit, unitType, loc, playerNumber, Cargo, rotation);
}