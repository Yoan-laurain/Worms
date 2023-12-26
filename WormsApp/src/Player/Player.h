#pragma once

#include <memory>
#include "Object/SActor.h"
#include "../Turn/ITurnObserver.h"

class WeaponStrategy;

class Player : public SActor, public ITurnObserver
{
	public : 

		Player();

		/* Begin ITurnObserver Implementation */

		void onTurnChange(int currentPlayer) override;

		/* End ITurnObserver Implementation */

		void SetWeaponStrategy(std::unique_ptr<WeaponStrategy> weaponStrategy);

		int currentHealth;
		int maxHealth;

private :
	// On utilise un pointeur unique pour s'assurer que le Player est le seul à posséder l'objet
	std::unique_ptr<WeaponStrategy> weaponStrategy; 

protected : 
	bool OnDamageTaken(int damage);
};