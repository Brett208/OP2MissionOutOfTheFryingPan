#pragma once

#include "TargetRegion.h"
#include "FightGroups/OffensiveFightGroup.h"

#include <vector>
#include <map>


class OffensiveStateManager
{
public:
	OffensiveStateManager(
		LOCATION northCommandCenterLoc, 
		LOCATION southCommandCenterLoc, 
		LOCATION northStructureFactoryLoc, 
		LOCATION southStructureFactoryLoc,
		OffensiveFightGroup& northFightGroup,
		OffensiveFightGroup& southFightGroup);
	void Update();

private:
	enum class MapState
	{
		WestAvailable,
		WestConsumed
	};

	const LOCATION NorthCommandCenterLoc;
	const LOCATION SouthCommandCenterLoc;
	const LOCATION NorthStructureFactoryLoc;
	const LOCATION SouthStructureFactoryLoc;

	OffensiveFightGroup& NorthFightGroup;
	OffensiveFightGroup& SouthFightGroup;

	struct MapArea
	{
		inline static const MAP_RECT NorthEast = MAP_RECT(
			LOCATION(210 + X_, 87 + Y_),
			LOCATION(256 + X_, 132 + Y_));

		inline static const MAP_RECT SouthEast = MAP_RECT(
			LOCATION(210 + X_, 133 + Y_),
			LOCATION(256 + X_, 178 + Y_));

		inline static const MAP_RECT North = MAP_RECT(
			LOCATION(55 + X_, 1 + Y_),
			LOCATION(256 + X_, 86 + Y_));

		inline static const MAP_RECT South = MAP_RECT(
			LOCATION(104 + X_, 179 + Y_),
			LOCATION(256 + X_, 256 + Y_));

		inline static const MAP_RECT West = MAP_RECT(
			LOCATION(58 + X_, 87 + Y_),
			LOCATION(137 + X_, 178 + Y_));
	};

	struct NorthBaseTarget
	{
		inline static const TargetRegion SouthEast{
			MapArea::SouthEast,
			std::vector<LOCATION>{
				LOCATION(230 + X_, 104 + Y_),
				LOCATION(217 + X_, 105 + Y_),
				LOCATION(220 + X_, 114 + Y_),
				LOCATION(233 + X_, 117 + Y_),
				LOCATION(236 + X_, 125 + Y_),
				LOCATION(239 + X_, 144 + Y_) } };

		inline static const TargetRegion North{
			MapArea::North,
			std::vector<LOCATION>{
				LOCATION(210 + X_, 67 + Y_) } };

		inline static const TargetRegion South{
		MapArea::South,
		std::vector<LOCATION>{
			LOCATION(210 + X_, 70 + Y_),
			LOCATION(170 + X_, 72 + Y_),
			LOCATION(120 + X_, 88 + Y_),
			LOCATION(103 + X_, 127 + Y_),
			LOCATION(107 + X_, 175 + Y_) } };

		inline static const TargetRegion West{
		MapArea::West,
		std::vector<LOCATION>{
			LOCATION(210 + X_, 70 + Y_),
			LOCATION(170 + X_, 72 + Y_),
			LOCATION(120 + X_, 88 + Y_) } };

		inline static const std::map<MapState, std::vector<TargetRegion>> targetMap
		{
			{ MapState::WestAvailable, { SouthEast, North, West, South } },
			{ MapState::WestConsumed, { SouthEast, North, South } }
		};
	};

	struct SouthBaseTarget
	{
		inline static const TargetRegion NorthEast{
		MapArea::NorthEast,
		std::vector<LOCATION>{
			LOCATION(220 + X_, 174 + Y_),
			LOCATION(227 + X_, 169 + Y_),
			LOCATION(233 + X_, 164 + Y_),
			LOCATION(234 + X_, 134 + Y_) } };

		inline static const TargetRegion North{
			MapArea::North,
			std::vector<LOCATION>{
				LOCATION(193 + X_, 194 + Y_),
				LOCATION(156 + X_, 190 + Y_),
				LOCATION(110 + X_, 172 + Y_),
				LOCATION(96 + X_, 129 + Y_),
				LOCATION(105 + X_, 86 + Y_) } };

		inline static const TargetRegion South{
			MapArea::South,
			std::vector<LOCATION>{
				LOCATION(206 + X_, 192 + Y_) } };

		inline static const TargetRegion West{
			MapArea::West,
			std::vector<LOCATION>{
				LOCATION(193 + X_, 194 + Y_),
				LOCATION(156 + X_, 190 + Y_),
				LOCATION(110 + X_, 172 + Y_),
				LOCATION(96 + X_, 129 + Y_) } };

		inline static const std::map<MapState, std::vector<TargetRegion>> targetMap
		{
			{ MapState::WestAvailable, { NorthEast, South, West, North } },
			{ MapState::WestConsumed, { NorthEast, South, North } }
		};
	};

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
	void SetFightGroupTargetRegions();
};
