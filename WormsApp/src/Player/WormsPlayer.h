#pragma once

#include "../Turn/ITurnObserver.h"
#include "../Weapons/WeaponStrategy.h" // On peut pas forward
#include "Objects/SPlayer.h"

class TextBlockWidget;
class ImageWidget;
class ButtonWidget;
class ProgressBarWidget;

class WormsPlayer : public SPlayer, public ITurnObserver
{
	GENERATE()

public :

		WormsPlayer();
		~WormsPlayer() override;

		/* Begin ITurnObserver Implementation */
		void onTurnChange(int currentPlayer) override;
		/* End ITurnObserver Implementation */

		void SetWeaponStrategy(std::unique_ptr<WeaponStrategy> weaponStrategy);
		WeaponStrategy* GetWeaponStrategy() const;

		bool OnDamageTaken(int damage);

		int PlayerId;
		float currentHealth;
private :

	void MoveVertical(float value, float sign);
	void MoveHorizontal(float value, float sign);
	void ApplyBinding();
	void Shoot();
	bool IsMyTurn();
	
	std::unique_ptr<WeaponStrategy> weaponStrategy;

	TextBlockWidget* healthText;
	ImageWidget* healthImage;
	ButtonWidget* UpgradeButton;
	ProgressBarWidget* healthBar;

	void UpgradeWeapon();

	float maxHealth;
	bool HasShot;

protected:
	void BeginPlay() override;
};