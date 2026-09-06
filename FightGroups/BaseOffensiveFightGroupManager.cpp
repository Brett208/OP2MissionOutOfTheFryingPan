#include "BaseOffensiveFightGroupManager.h"

void BaseOffensiveFightGroupManager::Update()
{
	for (auto& offensiveFightGroup : offensiveFightGroups) {
		offensiveFightGroup->UpdateTaskedFightGroups();
		if (offensiveFightGroup->IsFull() && canAttack) {
			offensiveFightGroup->Attack(offensiveTankCount);
		}
	}
}

void BaseOffensiveFightGroupManager::AddFightGroup(std::vector<Unit> vehicleFactories)
{
	OffensiveFightGroup offensiveFightGroup(aiPlayerNum, humanPlayerCount);
	offensiveFightGroup.Initialize(tankStagingArea, vehicleFactories, offensiveTankCount);
	offensiveFightGroups.push_back(std::make_unique<OffensiveFightGroup>(offensiveFightGroup));
}

std::string BaseOffensiveFightGroupManager::DebugMessage()
{
	return std::string("debugOFG: ") +
		std::string("Owner: ") + std::to_string(aiPlayerNum) +
		std::string(", Human Count : ") + std::to_string(humanPlayerCount) +
		std::string(", Factories : ") + std::to_string(offensiveFightGroup.vehicleFactoryCount());
}
