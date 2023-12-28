#pragma once

#include "Spoon.h"
#include "../Turn/TurnManager.h" // Forwards declaration ne fonctionne pas sur les unique_ptr
#include "../Field/Field.h" // Forwards declaration ne fonctionne pas sur les unique_ptr

#include <memory>

class WormLevel : public Level
{
	public:

		void CreatePlayer();

		void BeginPlay() override;

		std::unique_ptr<TurnManager> m_TurnManager;
		Field* m_Field;
};