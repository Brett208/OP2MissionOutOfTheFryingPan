#include "StrongBasesShared.h"
#include "DefensiveFightGroup.h"
#include "AIPlayer.h"

namespace
{
	int GetDefensiveTankCount()
	{
		int humanPlayerCount = HumanPlayerCount();
		switch (humanPlayerCount)
		{
		case 2: {
			return 3;
		}
		case 3: {
			return 5;
		}
		default: {
			return 8;
		}
		}
	}
}

void SetupDefensiveFightGroups(PlayerNum aiPlayerNum, const std::vector<Unit> vehicleFactories, MAP_RECT perimeterRect, MAP_RECT interiorRect)
{
	const std::vector<TargetTankCount> targetTanks{
	TargetTankCount{map_id::mapLynx, map_id::mapMicrowave, GetDefensiveTankCount()},
	TargetTankCount{map_id::mapLynx, map_id::mapESG, GetDefensiveTankCount()},
	TargetTankCount{map_id::mapLynx, map_id::mapEMP, GetDefensiveTankCount()},
	TargetTankCount{map_id::mapLynx, map_id::mapRPG, GetDefensiveTankCount()},
	TargetTankCount{map_id::mapLynx, map_id::mapStickyfoam, GetDefensiveTankCount()}
	};

	DefensiveFightGroup defensiveFightGroupPerimeter(aiPlayerNum, HumanPlayerCount());

	defensiveFightGroupPerimeter.Initialize(perimeterRect, vehicleFactories);
	defensiveFightGroupPerimeter.Populate(targetTanks);

	DefensiveFightGroup defensiveFightGroupBase(aiPlayerNum, HumanPlayerCount());

	defensiveFightGroupPerimeter.Initialize(interiorRect, vehicleFactories);
	defensiveFightGroupPerimeter.Populate(targetTanks);
}
