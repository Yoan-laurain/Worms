#pragma once

#include "../Turn/ITurnObserver.h"
#include "../Weapons/WeaponStrategy.h" // On peut pas forward
#include "Objects/SPlayer.h"

class WormsPlayer : public Player, public ITurnObserver
{
public : 

		WormsPlayer();


		/* Begin ITurnObserver Implementation */

		void onTurnChange(int currentPlayer) override;

		/* End ITurnObserver Implementation */

		void SetWeaponStrategy(std::unique_ptr<WeaponStrategy> weaponStrategy);

		int currentHealth;
		int maxHealth;

private :
	// On utilise un pointeur unique pour s'assurer que le Player est le seul � poss�der l'objet
	std::unique_ptr<WeaponStrategy> weaponStrategy; 

	void Move(float value, float sign);

protected : 
	bool OnDamageTaken(int damage);
};