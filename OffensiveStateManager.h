#pragma once

class OffensiveStateManager
{
public:
	OffensiveStateManager(LOCATION northCommandCenterLoc, LOCATION southCommandCenterLoc, LOCATION northStructureFactoryLoc, LOCATION southStructureFactoryLoc);
	void Update();

private:
	const LOCATION NorthCommandCenterLoc;
	const LOCATION SouthCommandCenterLoc;
	const LOCATION NorthStructureFactoryLoc;
	const LOCATION SouthStructureFactoryLoc;

	bool hasLavaConsumedCenterRegion = false;
	bool hasBlightEnteredWestRegion = false;
	bool isNorthBaseDestroyed = false;
	bool isSouthBaseDestroyed = false;

	bool CheckStructureDestroyed(map_id unitType, LOCATION loc);
	bool CheckCommandCenterDestroyed(LOCATION commandCenterLoc);
	bool CheckStructureFactoryDestroyed(LOCATION structureFactoryLoc);
	void CheckRegionCenterConsumed();
	void CheckRegionWestConsumed();
	void CheckNorthBaseDestroyed();
	void CheckSouthBaseDestroyed();
};
