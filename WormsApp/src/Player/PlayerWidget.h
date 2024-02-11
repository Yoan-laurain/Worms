#pragma once

#include <string>

#include "../Weapons/WeaponStrategy.h" // On peut pas forward

class ButtonWidget;
class ProgressBarWidget;
class WormsPlayer;
class TextBlockWidget;

class PlayerWidget 
{
	public : 

		PlayerWidget();
		PlayerWidget(WormsPlayer* player);

		void CreateHealthBar();
		void CreateWeaponButtons();
		ButtonWidget* CreateWeaponButton(const std::string& imagePath, std::shared_ptr<WeaponStrategy> weapon, float offsetX);
		void CreatePlayerName();
		void CreateLogoPlayer();
		void DisableWidget();
		void EnableWidget();
		void SelectCurentWeapon();
		void UpdateAmountOfAmmo();
		void CreateAmmunitionText(TextBlockWidget*& textWidget, ButtonWidget* button, int weaponIndex);

		void SetHealthBarProgress(float health,float maxHealth);
		void Init();

		ButtonWidget* SimpleGunButton;
		TextBlockWidget* SimpleGunText;

		ButtonWidget* GrenadeButton;
		TextBlockWidget* GrenadeText;

		ButtonWidget* GravitonButton;
		TextBlockWidget* GravitonText;

		ProgressBarWidget* healthBar;
		TextBlockWidget* playerName;

		WormsPlayer* player;

		int SectionForOnePlayer;
		int CenterOfSection;
};