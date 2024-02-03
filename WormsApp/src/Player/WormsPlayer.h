#pragma once

#include "../Turn/ITurnObserver.h"
#include "../Weapons/WeaponStrategy.h" // On peut pas forward
#include "Objects/SPlayer.h"

class WormsPlayer : public SPlayer, public ITurnObserver
{
	GENERATE()

public :

		WormsPlayer();
		~WormsPlayer();

		/* Begin ITurnObserver Implementation */
		void onTurnChange(int currentPlayer) override;
		/* End ITurnObserver Implementation */

		void SetWeaponStrategy(std::unique_ptr<WeaponStrategy> weaponStrategy);
		WeaponStrategy* GetWeaponStrategy() const;

		bool OnDamageTaken(int damage);

		int PlayerId;
		int currentHealth;
private :

	void MoveVertical(float value, float sign);
	void MoveHorizontal(float value, float sign);
	void ApplyBinding();
	void Shoot();
	bool IsMyTurn();
	
	// On utilise un pointeur unique pour s'assurer que le Player est le seul � poss�der l'objet
	std::unique_ptr<WeaponStrategy> weaponStrategy;

	int maxHealth;
	bool HasShot;
};