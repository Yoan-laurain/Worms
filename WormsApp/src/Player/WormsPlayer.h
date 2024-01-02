#pragma once

#include "../Turn/ITurnObserver.h"
#include "../Weapons/WeaponStrategy.h" // On peut pas forward
#include "Objects/SPlayer.h"

class WormsPlayer : public SPlayer, public ITurnObserver
{
	GENERATE()

public :

		WormsPlayer();


		/* Begin ITurnObserver Implementation */

		void onTurnChange(int currentPlayer) override;

		/* End ITurnObserver Implementation */

		void SetWeaponStrategy(std::unique_ptr<WeaponStrategy> weaponStrategy);

		int currentHealth;
		int maxHealth;

		class SSpriteComponent* SpriteComponent;

private :
	// On utilise un pointeur unique pour s'assurer que le Player est le seul � poss�der l'objet
	std::unique_ptr<WeaponStrategy> weaponStrategy; 

	void MoveVertical(float value, float sign);
	void MoveHorizontal(float value, float sign);

protected : 
	bool OnDamageTaken(int damage);
};