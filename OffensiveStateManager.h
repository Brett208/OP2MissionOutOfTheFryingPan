#pragma once

class OffensiveStateManager
{
public:
	void Update();

	LOCATION NorthCommandCenterLoc = LOCATION(0, 0);
	LOCATION SouthCommandCenterLoc = LOCATION(0, 0);
	LOCATION NorthStructureFactoryLoc = LOCATION(0, 0);
	LOCATION SouthStructureFactoryLoc = LOCATION(0, 0);
private:
	bool hasLavaConsumedCenterRegion = false;
	bool hasBlightEnteredWestRegion = false;
	bool isNorthBaseDestroyed = false;
	bool isSouthBaseDestroyed = false;
	
	void CheckRegionCenterConsumed();
	void CheckRegionWestConsumed();
	void CheckNorthBaseDestroyed();
	void CheckSouthBaseDestroyed();
};