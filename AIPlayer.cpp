#include "AIPlayer.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>
#include <stdexcept>
#include <algorithm>

// AI player is last player
PlayerNum GetAIIndex()
{
	for (int i = 0; i < 7; ++i)
	{
		if (!Player[i].IsHuman()) {
			return static_cast<PlayerNum>(i);
		}
	}

	throw std::runtime_error("No AI player detected");
}

	//Note: Scenario must have 5 or fewer human players to work.
	PlayerColor GetAIColor(bool allowBlack)
	{
		int totalColors = 6;
		if (allowBlack) {
			totalColors++;
		}

		std::vector<int> availableColors;
		for (int i = 0; i < totalColors; ++i) {
			availableColors.push_back(i);
		}

		for (int i = 0; i < TethysGame::NoPlayers() - 1; ++i)
		{
			availableColors.erase(
				std::remove(availableColors.begin(), availableColors.end(), ExtPlayer[i].GetColorNumber()), availableColors.end());
		}

		if (availableColors.size() == 0) {
			return PlayerColor::PlayerBlue;
		}

		const int colorIndex = TethysGame::GetRand(availableColors.size());

		return static_cast<PlayerColor>(availableColors[colorIndex]);
	}

	void AIInitialization()
	{
		LOCATION AIWeakBaseLoc(50 + X_, 50 + Y_);
		PlayerNum aiIndex = GetAIIndex();
		Player[aiIndex].GoAI();
		Player[aiIndex].SetColorNumber(GetAIColor());
		BuildAIBase(aiIndex, AIWeakBaseLoc);
	}