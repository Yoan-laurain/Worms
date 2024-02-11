#pragma once

#include "../Turn/ITurnObserver.h"
#include "../Weapons/WeaponStrategy.h" // On peut pas forward
#include "Objects/SPlayer.h"

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

		int PlayerId;
		float currentHealth;
		float maxHealth;
private :

	void MoveVertical(float value, float sign);
	void MoveHorizontal(float value, float sign);
	void ApplyBinding();
	void Shoot();
	bool IsMyTurn();

	std::shared_ptr<WeaponStrategy> weaponStrategy;

	void CreateHUD();

	std::unique_ptr<PlayerWidget> playerWidget;

	bool HasShot;
};