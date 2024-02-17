#pragma once

#include "../Turn/TurnManager.h" 
#include <Core/Level.h>
#include <Library/TStruct.h>
#include <memory>

class WindWidget;
class Field;
class GrenadeFragment;

class WormLevel : public Level
{
	public:

		WormLevel();
		~WormLevel() override = default;
	
		void SpawnPlayers();
		void SpawnField();
		void CreatePlayer(FTransform SpawnLocation, int PlayerId);
	
		void OnGrenadeFragmentDestroy();
	
		WindWidget* MyWindWidget;

		std::unique_ptr<TurnManager> ATurnManager;
	
		std::vector<GrenadeFragment*> GrenadeFragments;
		int NumberOfGrenadeFragmentsRemaining = 3;
	
	private:
		Field* MyField;

	protected:
		void BeginPlay() override;
};