#pragma once

#include "../Turn/TurnManager.h" 
#include <Core/Level.h>
#include <Library/TStruct.h>
#include <memory>

class WindWidget;
class Field;

class WormLevel : public Level
{
	public:

		WormLevel();
		~WormLevel() override = default;
	
		void SpawnPlayers();
		void SpawnField();
		void CreatePlayer(FTransform& SpawnLocation, int PlayerId);
	
		WindWidget* MyWindWidget;

		std::unique_ptr<TurnManager> ATurnManager;
	
	private:
		Field* MyField;

	protected:
		void BeginPlay() override;
};