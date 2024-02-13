#pragma once

#include "../Turn/ITurnObserver.h"
#include "../Weapons/WeaponStrategy.h" // On peut pas forward
#include "Objects/SPlayer.h"
#include <Library/TColor.h>
#include <SFML/System.hpp>

class PlayerWidget;

class WormsPlayer : public SPlayer, public ITurnObserver
{
	GENERATE()

public :

		WormsPlayer();
		~WormsPlayer() override;

		/* Begin ITurnObserver Implementation */
		void onTurnChange(int currentPlayer) override;
		/* End ITurnObserver Implementation */

		void SetWeaponStrategy(std::shared_ptr<WeaponStrategy> weapon);
		WeaponStrategy* GetWeaponStrategy() const;

		bool OnDamageTaken(int damage);
		void Init();
		void ChangeTurn();

		int PlayerId;
		float currentHealth;
		float maxHealth;
		std::vector<std::shared_ptr<WeaponStrategy>> weapons;

	private :

		void ApplyBinding();

		void MoveVertical(float value, float sign);
		void MoveHorizontal(float value, float sign);
		void UpdateSpriteDirection(FVector2D direction);
		void Shoot();
		void Reload();

		bool IsMyTurn();
		void CreateHUD();

		std::shared_ptr<WeaponStrategy> weaponStrategy;
		PlayerWidget* playerWidget;

		bool HasShot;
		bool BeenHit;

		FColor HitColor;
		FColor DefaultColor;

		sf::Clock TimerBeingHit;

protected:
	void Tick(float DeltaTime) override;
};