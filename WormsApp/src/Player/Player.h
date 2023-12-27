#pragma once

#include "Object/SActor.h"
#include "../Turn/ITurnObserver.h"
#include "../Weapons/WeaponStrategy.h"

class WeaponStrategy;

class Player : public SActor, public ITurnObserver
{
	public : 

		Player();

		virtual ~Player() = default;


		/* Begin ITurnObserver Implementation */

		void onTurnChange(int currentPlayer) override;

		/* End ITurnObserver Implementation */

		void SetWeaponStrategy(std::unique_ptr<WeaponStrategy> weaponStrategy);

		int currentHealth;
		int maxHealth;

		class GravityComposant* GravityComponent;

protected:

	virtual void Tick(float DeltaTime) override;

private :
	// On utilise un pointeur unique pour s'assurer que le Player est le seul � poss�der l'objet
	std::unique_ptr<WeaponStrategy> weaponStrategy; 

protected : 
	bool OnDamageTaken(int damage);
};