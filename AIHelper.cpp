#include "AIHelper.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"

void SetupMiningGroup(
	MiningGroup &miningGroup, Unit &mine, Unit &smelter, MAP_RECT &oreIdleRect, int numbOfTrucks, PlayerNum aiPlayerNum)
{
	miningGroup = CreateMiningGroup(Player[aiPlayerNum]);

	LOCATION smelterLoc = smelter.Location();
	miningGroup.Setup(mine, smelter, oreIdleRect);

	Unit truck;
	for (int i = 0; i < numbOfTrucks; ++i)
	{
		TethysGame::CreateUnit(truck, map_id::mapCargoTruck, oreIdleRect.RandPt(), aiPlayerNum, map_id::mapNone, South);
		miningGroup.TakeUnit(truck);
		truck.DoSetLights(true);
	}

	miningGroup.SetTargCount(map_id::mapCargoTruck, map_id::mapNone, numbOfTrucks);
}