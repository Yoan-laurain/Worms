#pragma once

#include "../Turn/ITurnObserver.h"
#include "../Weapons/WeaponStrategy.h" 
#include <Objects/SPlayer.h>
#include <Library/TColor.h>
#include <SFML/System.hpp>

class WormsPlayerController;
class PlayerWidget;

class WormsPlayer : public SPlayer, public ITurnObserver
{
	GENERATE()

	public :

		WormsPlayer();
		~WormsPlayer() override;

		/* Begin ITurnObserver Implementation */
		void OnTurnChange(int CurrentPlayer) override;
		/* End ITurnObserver Implementation */

		void Init();
		bool OnDamageTaken(int Damage);
		void ChangeTurn();
		bool IsMyTurn() const;
	
		int PlayerId;
		float CurrentHealth;
		float MaxHealth;
		bool bHasShot;
	
		PlayerWidget* MyPlayerWidget;
	
		std::vector<std::shared_ptr<WeaponStrategy>> Weapons;
		std::shared_ptr<WeaponStrategy> WeaponStrategy;

	private :
	
		void CreateHUD();
		void DisplayHitEffect(float DeltaTime);
		void SetBeingHit(bool BeingHit);
		void HandlePlayerDeath();
	
		WormsPlayerController* PlayerController;
	
		bool bBeenHit;

		FColor HitColor;
		FColor DefaultColor;

		sf::Clock TimerBeingHit;

	protected:
		void Tick(float DeltaTime) override;
};