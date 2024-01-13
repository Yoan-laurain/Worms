#pragma once

#include "../Turn/TurnManager.h" // Forwards declaration ne fonctionne pas sur les unique_ptr
#include "Core/Level.h"
#include "Library/TStruct.h"

#include <memory>

class Field;

class WormLevel : public Level
{
	public:

		WormLevel();

		void CreatePlayer(const FTransform& SpawnLocation);

		void BeginPlay() override;

		FTransform SpawnLocation;

private:
		std::unique_ptr<TurnManager> m_TurnManager;
		Field* m_Field;
};