#pragma once

#include "Spoon.h"

class TurnManager;

class WormLevel : public Level
{
	public:

		void CreatePlayer(TurnManager& turnManager);

		void BeginPlay() override;
};