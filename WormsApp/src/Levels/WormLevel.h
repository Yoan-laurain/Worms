#pragma once

#include "../Turn/TurnManager.h" // Forwards declaration ne fonctionne pas sur les unique_ptr
#include "Core/Level.h"
#include "Library/TStruct.h"

#include <memory>

class Field;
class ImageWidget;

class WormLevel : public Level
{
	public:

		WormLevel();

		void CreatePlayer(const FTransform& SpawnLocation, int PlayerId);

		void BeginPlay() override;
		void CreateWind();
		void UpdateWindDirection(float windDirection);

		FTransform SpawnLocation;

		ImageWidget* WindLogo;
		ImageWidget* WindDirection;

		std::unique_ptr<TurnManager> m_TurnManager;
private:
		Field* m_Field;
};