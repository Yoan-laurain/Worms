#pragma once

#include "Spoon.h"
#include <memory>

#include "../Turn/TurnManager.h"

class WormLevel : public Level
{
	public:

		void CreatePlayer();

		void BeginPlay() override;

		std::unique_ptr<TurnManager> m_TurnManager;
};