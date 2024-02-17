#include "PlayerWidget.h"
#include "../../Player/WormsPlayer.h"
#include "../../Config.h"
#include "../../Levels/WormLevel.h"
#include <Widgets/TextBlock/TextBlockWidget.h>
#include <Widgets/ProgressBar/ProgressBarWidget.h>
#include <Widgets/Button/ButtonWidget.h>
#include <Widgets/Image/ImageWidget.h> 
#include <Library/WidgetHandler.h>
#include <Core/Application.h>
#include <Renders/SFML/SfmlWindow.h>

PlayerWidget::PlayerWidget()
	: Player(nullptr)
	, bIsTimerActive(false)
	, ButtonSize(50)
	, SimpleGunButton(nullptr)
	, SimpleGunText(nullptr)
	, GrenadeButton(nullptr)
	, GrenadeText(nullptr)
	, GravitonButton(nullptr)
	, GravitonText(nullptr)
	, HealthBar(nullptr)
	, PlayerName(nullptr)
	, TimerText(nullptr)
{

}

void PlayerWidget::Init()
{
	CreateHealthBar();
	CreateWeaponButtons();
	CreatePlayerName();
	CreateLogoPlayer();
}

void PlayerWidget::Tick(float DeltaTime)
{
	Widget::Tick(DeltaTime);

	if (bIsTimerActive)
	{
		UpdateTimer();
	}
}

void PlayerWidget::Render()
{
}

void PlayerWidget::CreateHealthBar()
{
	HealthBar = WidgetHandler::CreateWidget<ProgressBarWidget>(Player);
	
	HealthBar->Size = FVector2D(100.f, 10.f);
	HealthBar->RelativePosition = FVector2D(-HealthBar->Size.X / 2.f, -Player->GetSize().Y * 2);
	HealthBar->BaseStyle = { FColor(127, 127, 127, 150), FColor(0, 0, 0, 0), 0.f };
	HealthBar->Color = FColor(0, 255, 0, 255);
	SetHealthBarProgress(Player->CurrentHealth, Player->MaxHealth);
	
	HealthBar->AddToViewport();
}

void PlayerWidget::CreateWeaponButtons()
{
	SimpleGunButton = CreateWeaponButton(Config::SimpleGun, Player->Weapons[0], -ButtonSize);
	GrenadeButton = CreateWeaponButton(Config::GrenadeLauncher, Player->Weapons[1], 0.f);
	GravitonButton = CreateWeaponButton(Config::Graviton, Player->Weapons[2], ButtonSize);
	
	SimpleGunText = CreateAmmunitionText(SimpleGunButton);
	GrenadeText = CreateAmmunitionText(GrenadeButton);
	GravitonText = CreateAmmunitionText(GravitonButton);

	WeaponsWidgets[Player->Weapons[0].get()] = new WeaponWidget(SimpleGunButton, SimpleGunText);
	WeaponsWidgets[Player->Weapons[1].get()] = new WeaponWidget(GrenadeButton, GrenadeText);
	WeaponsWidgets[Player->Weapons[2].get()] = new WeaponWidget(GravitonButton, GravitonText);

	UpdateAmountOfAmmo();
}

ButtonWidget* PlayerWidget::CreateWeaponButton(const std::string& ImagePath, std::shared_ptr<WeaponStrategy> Weapon, float OffsetX)
{
	ButtonWidget* Button = WidgetHandler::CreateWidget<ButtonWidget>(nullptr);

	if (Button)
	{
		Button->Size = FVector2D(ButtonSize);
		Button->RelativePosition = FVector2D(Config::CenterOfSection + Config::SectionForOnePlayer * Player->PlayerId + OffsetX - Button->Size.X / 2.f, 100.f);
	
		Button->SetBackgroundImage(ImagePath);

		std::function OnClick = [this, Weapon]()
		{
			if ( Player )
				Player->WeaponStrategy = Weapon;
		};

		Button->OnClick = OnClick;

		Button->SetIsEnabled(true);
		Button->AddToViewport();
	}
	
	return Button;
}

TextBlockWidget* PlayerWidget::CreateAmmunitionText(ButtonWidget* Button)
{
	TextBlockWidget* TextWidget = WidgetHandler::CreateWidget<TextBlockWidget>(Button);

	if ( TextWidget )
	{
		TextWidget->FontSize = 10;
		TextWidget->RelativePosition = FVector2D(Button->Size.X * 0.55f, Button->Size.Y * 0.75f);
	
		TextWidget->AddToViewport();
	}
	
	return TextWidget;
}

void PlayerWidget::SetHealthBarProgress(float Health, float MaxHealth)
{
	if (HealthBar)
		HealthBar->Progress = Health / MaxHealth;
}

void PlayerWidget::SetWeaponsButtonEnabled(bool bEnabled)
{
	for (auto& Weapon : WeaponsWidgets)
	{
		Weapon.second->Button->SetIsEnabled(bEnabled);
	}
}

void PlayerWidget::CreatePlayerName()
{
	PlayerName = WidgetHandler::CreateWidget<TextBlockWidget>(nullptr);

	if ( PlayerName )
	{
		PlayerName->Text = "Player " + std::to_string(Player->PlayerId);
		PlayerName->FontSize = 20;
		PlayerName->RelativePosition = FVector2D(Config::CenterOfSection + Config::SectionForOnePlayer * Player->PlayerId -
										(PlayerName->Text.size() * PlayerName->FontSize) / 4.f, 50.f + PlayerName->FontSize);
	
		PlayerName->AddToViewport();
	}
}

void PlayerWidget::CreateLogoPlayer()
{
	ImageWidget* Logo = WidgetHandler::CreateWidget<ImageWidget>(nullptr);

	if ( Logo )
	{
		Logo->Size = FVector2D(ButtonSize);
		Logo->RelativePosition = FVector2D(Config::CenterOfSection + Config::SectionForOnePlayer * Player->PlayerId - Logo->Size.X / 2.f, 20.f);
		Logo->ImagePath = Player->PlayerId == 0 ? Config::Player1Right : Config::Player2Right;

		Logo->AddToViewport();
	}
}

void PlayerWidget::SelectCurrentWeapon()
{
	for (auto& Weapon : WeaponsWidgets)
	{
		if ( Weapon.first == Player->WeaponStrategy.get() )
		{
			Weapon.second->Button->bIsSelected = true;
			break;
		}
	}
}

void PlayerWidget::UpdateAmountOfAmmo()
{
	for (auto& Weapon : Player->Weapons)
	{
		if (auto& Widget = WeaponsWidgets[Weapon.get()])
		{
			Widget->Text->Text = std::to_string(Weapon->CurrentAmmunition) + "/" + std::to_string(Weapon->MunitionInMagazine);
		}
	}
}

#pragma region Timer

void PlayerWidget::StartTimer()
{
	Clock.restart();
	bIsTimerActive = true;
	
	TimerText = WidgetHandler::CreateWidget<TextBlockWidget>(nullptr);

	if ( TimerText )
	{
		TimerText->FontSize = 20;
		TimerText->AddToViewport(); 
	}
}

void PlayerWidget::StopTimer()
{
	bIsTimerActive = false;
}

void PlayerWidget::DestroyTimer()
{
	if (TimerText)
	{
		StopTimer();
		TimerText->RemoveFromParent();
		TimerText = nullptr;
	}
}

void PlayerWidget::UpdateTimer()
{
	const float TimeElapsed = Clock.getElapsedTime().asSeconds();
	const float RemainingTime = Config::TimerForATurn - TimeElapsed;
	
	if (RemainingTime <= 0 )
	{
		DestroyTimer();
		Player->ChangeTurn();
		return;
	}
	
	const float RemainingTimeMs = (RemainingTime - static_cast<int>(RemainingTime)) * 100;

	const std::string Time = std::to_string(static_cast<int>(RemainingTime)) + ":" + std::to_string(static_cast<int>(RemainingTimeMs));

	if ( TimerText )
	{
		TimerText->Text = Time;

		TimerText->RelativePosition = FVector2D(Config::SectionForOnePlayer - (TimerText->Text.size() * TimerText->FontSize) / 4.f,
			20.f + TimerText->FontSize);
	}
}

#pragma endregion Timer