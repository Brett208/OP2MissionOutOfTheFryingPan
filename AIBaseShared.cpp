#include "AIBaseShared.h"
#include "AIHelper.h"
#include "AIPlayer.h"

const std::vector<GuardPostData> guardPostCluster =
{
	{ LOCATION(0, 0), mapEMP},
	{ LOCATION(0, 2), mapESG},
	{ LOCATION(2, 1), mapStickyfoam}
};

PlayerNum aiPlayerIndex = Player0;

void SetAIIndex(PlayerNum playerNum)
{
	aiPlayerIndex = playerNum;
}

void CreatePlymouthGuardPostCluster(LOCATION loc, std::vector<Unit>& buildings)
{
	CreateGuardPostCluster(aiPlayerIndex, loc, guardPostCluster, buildings);
}

void RecordPlymouthGuardPostCluster(LOCATION loc, BuildingGroup& buildingGroup)
{
	RecordGuardPostCluster(loc, guardPostCluster, buildingGroup);
}
