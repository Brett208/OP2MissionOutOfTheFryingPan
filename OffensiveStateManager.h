#pragma once

class OffensiveStateManager
{
public:
	void Update();
	void Initialize(LOCATION northCommandCenterLoc, LOCATION southCommandCenterLoc, LOCATION northStructureFactoryLoc, LOCATION southStructureFactoryLoc);

	LOCATION NorthCommandCenterLoc = LOCATION(0, 0);
	LOCATION SouthCommandCenterLoc = LOCATION(0, 0);
	LOCATION NorthStructureFactoryLoc = LOCATION(0, 0);
	LOCATION SouthStructureFactoryLoc = LOCATION(0, 0);
private:
	bool hasLavaConsumedCenterRegion = false;
	bool hasBlightEnteredWestRegion = false;
	bool isNorthBaseDestroyed = false;
	bool isSouthBaseDestroyed = false;
	
	bool CheckCommandCenterDestroyed(LOCATION commandCenterLoc);
	bool CheckStructureFactoryDestroyed(LOCATION structureFactoryLoc);
	void CheckRegionCenterConsumed();
	void CheckRegionWestConsumed();
	void CheckNorthBaseDestroyed();
	void CheckSouthBaseDestroyed();
};