#include "PlayerInitialization.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include<array>
#include<vector>

void InitializePlayer(PlayerNum playerNumber, const LOCATION& initBaseLoc);
void SelectInitialUnit(int index, const LOCATION& Location, PlayerNum playerNumber);
map_id GetInitialWeapon(PlayerNum playerNumber);
void CreateInitialUnit(Unit& unit, map_id unitType, const LOCATION& loc, PlayerNum playerNumber, map_id Cargo);

const std::array<LOCATION, 4> playerStartLocs{
	LOCATION(147 + X_, 110 + Y_),
	LOCATION(172 + X_, 110 + Y_),
	LOCATION(141 + X_, 148 + Y_),
	LOCATION(158 + X_, 133 + Y_),
};

const ResourceSet resourceSet{
	{
		// Kids, Adults, Scientist, Food, Common, Rare
		{ 27, 18, 22, 4000, 2000, 0 },		// Easy
		{ 24, 15, 20, 3500, 1500, 0 },		// Medium
		{ 20, 12, 18, 3000, 1000, 0 },		// Hard
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

	Player[playerNumber].CenterViewOn(initBaseLoc.x, initBaseLoc.y);

	CreateInitialUnit(unit, mapCommandCenter, initBaseLoc, playerNumber, map_id::mapNone); //ComandCenter
	currentLoc.y = initBaseLoc.y - 6;

	CreateInitialUnit(unit, mapBasicLab, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.y = initBaseLoc.y - 4;

	CreateInitialUnit(unit, mapBasicLab, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.y = initBaseLoc.y + 6;

	CreateInitialUnit(unit, mapCommonOreSmelter, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x = initBaseLoc.x - 4;
	currentLoc.y = initBaseLoc.y;

	CreateInitialUnit(unit, mapStructureFactory, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x = initBaseLoc.x + 4;

	CreateInitialUnit(unit, mapAgridome, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x = initBaseLoc.x + 7;
	currentLoc.y = initBaseLoc.y - 7;

	CreateInitialUnit(unit, mapTokamak, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x = initBaseLoc.x;
	currentLoc.y = initBaseLoc.y + 9;

	CreateTubeLine(initBaseLoc + LOCATION(0, -3), initBaseLoc + LOCATION(0, -1));
	CreateTubeLine(initBaseLoc + LOCATION(0, 1), initBaseLoc + LOCATION(0, 5));
	CreateTubeLine(initBaseLoc + LOCATION(-2, 0), initBaseLoc + LOCATION(-1, 0));
	CreateTubeLine(initBaseLoc + LOCATION(1, 0), initBaseLoc + LOCATION(3, 0));

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

	CreateInitialUnit(unit, map_id::mapCargoTruck, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x++;
	CreateInitialUnit(unit, map_id::mapCargoTruck, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x++;
	CreateInitialUnit(unit, map_id::mapCargoTruck, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x++;
	CreateInitialUnit(unit, map_id::mapCargoTruck, currentLoc, playerNumber, map_id::mapNone);

	currentLoc.x = vechStartLoc.x;
	currentLoc.y++;

	CreateInitialUnit(unit, map_id::mapEarthworker, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x++;
	CreateInitialUnit(unit, map_id::mapRoboMiner, currentLoc, playerNumber, map_id::mapNone);
	currentLoc.x++;
	CreateInitialUnit(unit, map_id::mapRoboSurveyor, currentLoc, playerNumber, map_id::mapNone);

	// 1. Lynx
	// 2. Lynx
	// 3. Robo-Dozer
	// 4. Earthworker
	// 5. Robo-Miner
	// 6. ConVec - Guard Post
	// 7. ConVec - Guard Post
	// 8. Truck
	// 9. Robo-Surveyor
	// 10. Scout
	// 11. ConVec - Guard Post
	// 12. Truck

	
	
	for (int i = 0; i < TethysGame::InitialUnits(); ++i)
	{
		currentLoc.x = vechStartLoc.x + i % 4;
		currentLoc.y = vechStartLoc.y + 4 + i / 4;

		SelectInitialUnit(i, currentLoc, playerNumber);
	}
}


void SelectInitialUnit(int index, const LOCATION& location, PlayerNum playerNumber)
{
	Unit unit;
	
	switch (index)
	{

	case 1:
	case 2: {
		map_id cargo = GetInitialWeapon(playerNumber);
		CreateInitialUnit(unit, map_id::mapLynx, location, playerNumber, cargo);
		break; }

	case 3: {
		CreateInitialUnit(unit, map_id::mapRoboDozer, location, playerNumber, map_id::mapNone);
		break; }

	case 4: {
		CreateInitialUnit(unit, map_id::mapEarthworker, location, playerNumber, map_id::mapNone);
		break; }

	case 5: {
		CreateInitialUnit(unit, map_id::mapRoboMiner, location, playerNumber, map_id::mapNone);
		break; }

	case 6:
	case 7:
	case 11: {
		CreateInitialUnit(unit, map_id::mapConVec, location, playerNumber, map_id::mapGuardPost);
		break; }

	case 8:
	case 12: {
		CreateInitialUnit(unit, map_id::mapCargoTruck, location, playerNumber, map_id::mapNone);
		break; }

	case 9: {
		CreateInitialUnit(unit, map_id::mapRoboSurveyor, location, playerNumber, map_id::mapNone);
		break; }

	case 10: {
		CreateInitialUnit(unit, map_id::mapScout, location, playerNumber, map_id::mapNone);
		break; }

	}
}

map_id GetInitialWeapon(PlayerNum playerNumber) {
	map_id cargo = map_id::mapMicrowave;
	if (Player[playerNumber].IsEden()) {
		cargo = map_id::mapLaser;
		return cargo;
	}
}

void CreateInitialUnit(Unit& unit, map_id unitType, const LOCATION& loc, PlayerNum playerNumber, map_id Cargo)
{
	const UnitDirection rotation = UnitDirection::South;
	TethysGame::CreateUnit(unit, unitType, loc, playerNumber, Cargo, rotation);
	unit.DoSetLights(true);
}