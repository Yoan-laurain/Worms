#pragma once

#include "../../Weapons/WeaponStrategy.h"
#include <Spoon/Widgets/Widget.h>
#include <string>
#include <SFML/Graphics.hpp>

class ButtonWidget;
class ProgressBarWidget;
class WormsPlayer;
class TextBlockWidget;
class ImageWidget;

struct WeaponWidget
{
	ButtonWidget* Button;
	TextBlockWidget* Text;
};

class PlayerWidget : public Widget
{
	public : 

		PlayerWidget();
		~PlayerWidget() override = default;
	
		void Init();
		void SetHealthBarProgress(float Health,float MaxHealth);

		void SetWeaponsButtonEnabled(bool bEnabled);

		void StartTimer();
		void DestroyTimer();
		void StopTimer();

		void SelectCurrentWeapon();
		void UpdateAmountOfAmmo();

		WormsPlayer* Player;

	private:
	
		void CreateHealthBar();
	
		void CreateWeaponButtons();
		ButtonWidget* CreateWeaponButton(const std::string& ImagePath, std::shared_ptr<WeaponStrategy> Weapon, float OffsetX);

		void CreatePlayerName();
		void CreateLogoPlayer();
		TextBlockWidget* CreateAmmunitionText(ButtonWidget* Button);
	
		void UpdateTimer();

		bool bIsTimerActive;

		sf::Clock Clock;

		float ButtonSize;

#pragma region Widgets

		ButtonWidget* SimpleGunButton;
		TextBlockWidget* SimpleGunText;

		ButtonWidget* GrenadeButton;
		TextBlockWidget* GrenadeText;

		ButtonWidget* GravitonButton;
		TextBlockWidget* GravitonText;

		ProgressBarWidget* HealthBar;
		TextBlockWidget* PlayerName;

		TextBlockWidget* TimerText;

		std::map< WeaponStrategy*, WeaponWidget*> WeaponsWidgets;

#pragma endregion Widgets

	protected:
		void Tick(float DeltaTime) override;
		void Render() override;
};