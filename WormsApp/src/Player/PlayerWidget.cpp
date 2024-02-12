#include "PlayerWidget.h"
#include "../Weapons/SimpleGun/SimpleGun.h"
#include "../Weapons/FragGrenade/GrenadeLauncher.h"
#include "../Config.h"
#include "WormsPlayer.h"
#include <Widgets/TextBlock/TextBlockWidget.h>
#include <Widgets/ProgressBar/ProgressBarWidget.h>
#include <Widgets/Button/ButtonWidget.h>
#include <Widgets/Image/ImageWidget.h> 
#include <Library/WidgetHandler.h>
#include <Core/Application.h>
#include <Core/Window.h>
#include <Renders/SFML/SfmlWindow.h>
#include "../Levels/WormLevel.h"

PlayerWidget::PlayerWidget()
	: player(nullptr)
	, SimpleGunButton(nullptr)
	, GrenadeButton(nullptr)
	, healthBar(nullptr)
	, playerName(nullptr)
	, SectionForOnePlayer(0)
	, CenterOfSection(0)
	, SimpleGunText(nullptr)
	, GrenadeText(nullptr)
	, GravitonButton(nullptr)
	, GravitonText(nullptr)
	, clock()
	, TimerText(nullptr)
	, isTimerActive(false)
{

}

PlayerWidget::PlayerWidget(WormsPlayer* player) 
	: player(player)
	, SimpleGunButton(nullptr)
	, GrenadeButton(nullptr)
	, healthBar(nullptr)
	, playerName(nullptr)
	, SectionForOnePlayer(0)
	, CenterOfSection(0)
	, SimpleGunText(nullptr)
	, GrenadeText(nullptr)
	, GravitonButton(nullptr)
	, GravitonText(nullptr)
	, clock()
	, TimerText(nullptr)
	, isTimerActive(false)
{
}

void PlayerWidget::Init()
{
	int widthWindow = Application::Get().GetWindow()->GetWidth();
	SectionForOnePlayer = widthWindow / Config::MaxPlayers;
	CenterOfSection = SectionForOnePlayer / 2.f;

	CreateHealthBar();
	CreateWeaponButtons();
	CreatePlayerName();
	CreateLogoPlayer();
}

void PlayerWidget::StartTimer()
{
	clock.restart();
	TimerText = WidgetHandler::CreateWidget<TextBlockWidget>(nullptr);
	TimerText->fontSize = 20;
	TimerText->AddToViewport(); 

	isTimerActive = true;
}

void PlayerWidget::StopTimer()
{
	isTimerActive = false;
}

void PlayerWidget::DestroyTimer()
{
	if (TimerText)
	{
		StopTimer();
		TimerText->RemoveFromParent();
	}
}

void PlayerWidget::UpdateTimer(float deltaTime)
{
	float timeElapsed = clock.getElapsedTime().asSeconds();
	float remainingTime = 15.f - timeElapsed;

	float remainingTimeMs = (remainingTime - (int)remainingTime) * 100;

	if (remainingTime <= 0 && remainingTimeMs <= 0)
	{
		DestroyTimer();
		player->ChangeTurn();
		return;
	}

	std::string time = std::to_string((int)remainingTime) + ":" + std::to_string((int)remainingTimeMs);
	TimerText->text = time;

	TimerText->relativePosition = FVector2D(SectionForOnePlayer - (TimerText->text.size() * TimerText->fontSize) / 4.f,
		20.f + TimerText->fontSize);
}

void PlayerWidget::Tick(float deltaTime)
{
	Widget::Tick(deltaTime);

	if (!isTimerActive)
		return;

	UpdateTimer(deltaTime);

	// TODO: Move this to the level
	Level* level = Application::Get().GetWorld();
	dynamic_cast<WormLevel*>(level)->UpdateWindDirection(dynamic_cast<WormLevel*>(level)->WindDirection->rotation + 40.f * deltaTime);
}

void PlayerWidget::render()
{
}

void PlayerWidget::CreateHealthBar()
{
	healthBar = WidgetHandler::CreateWidget<ProgressBarWidget>(player);
	healthBar->size = FVector2D(100.f, 10.f);
	healthBar->relativePosition = FVector2D(-healthBar->size.X / 2.f, -player->GetSize().Y * 2);
	SetHealthBarProgress(player->currentHealth, player->maxHealth);
	healthBar->BackgroundColor = FColor(127, 127, 127, 150);
	healthBar->color = FColor(0, 255, 0, 255);
	healthBar->AddToViewport();
}

void PlayerWidget::CreateWeaponButtons()
{
	SimpleGunButton = CreateWeaponButton("Ressources/SimpleGun.png", player->weapons[0], -50.f);
	GrenadeButton = CreateWeaponButton("Ressources/GrenadeLauncher.png", player->weapons[1], 0.f);
	GravitonButton = CreateWeaponButton("Ressources/Graviton.png", player->weapons[2], 50.f);

	CreateAmmunitionText(SimpleGunText, SimpleGunButton, 0);
	CreateAmmunitionText(GrenadeText, GrenadeButton, 1);
	CreateAmmunitionText(GravitonText, GravitonButton, 2);

	UpdateAmountOfAmmo();
}

void PlayerWidget::CreateAmmunitionText(TextBlockWidget*& textWidget, ButtonWidget* button, int weaponIndex)
{
	textWidget = WidgetHandler::CreateWidget<TextBlockWidget>(button);

	textWidget->fontSize = 10;
	textWidget->relativePosition = FVector2D(20.f, 38.f);
	textWidget->AddToViewport();
}

void PlayerWidget::SetHealthBarProgress(float health, float maxHealth)
{
	healthBar->progress = health / maxHealth;
}

ButtonWidget* PlayerWidget::CreateWeaponButton(const std::string& imagePath, std::shared_ptr<WeaponStrategy> weapon, float offsetX)
{
	ButtonWidget*  button = WidgetHandler::CreateWidget<ButtonWidget>(nullptr);
	button->size = FVector2D(50.f, 50.f);
	button->relativePosition = FVector2D(CenterOfSection + SectionForOnePlayer * player->PlayerId + offsetX - button->size.X / 2.f, 100.f);
	button->BackgroundColor = FColor(127, 127, 127, 50);
	button->SetBackgroundImage(imagePath);

	std::function<void()> onClick = [this, weapon]()
	{
		player->SetWeaponStrategy(weapon);
	};

	button->onClick = onClick;

	button->SetIsEnabled(true);
	button->AddToViewport();
	return button;
}

void PlayerWidget::CreatePlayerName()
{
	playerName = WidgetHandler::CreateWidget<TextBlockWidget>(nullptr);
	playerName->text = "Player " + std::to_string(player->PlayerId);
	playerName->fontSize = 20;
	playerName->relativePosition = FVector2D(CenterOfSection + SectionForOnePlayer * player->PlayerId -
									(playerName->text.size() * playerName->fontSize) / 4.f, 50.f + playerName->fontSize);
	playerName->AddToViewport();
}

void PlayerWidget::CreateLogoPlayer()
{
	ImageWidget* logo = WidgetHandler::CreateWidget<ImageWidget>(nullptr);
	logo->size = FVector2D(50.f, 50.f);
	logo->relativePosition = FVector2D(CenterOfSection + SectionForOnePlayer * player->PlayerId - logo->size.X / 2.f, 20.f);
	logo->imagePath = player->PlayerId == 0 ? "Ressources/WormsPlayer.png" : "Ressources/WormsPlayer2.png";
	logo->AddToViewport();
}

void PlayerWidget::DisableWidget()
{
	SimpleGunButton->SetIsEnabled(false);
	GrenadeButton->SetIsEnabled(false);
	GravitonButton->SetIsEnabled(false);
}

void PlayerWidget::EnableWidget()
{
	SimpleGunButton->SetIsEnabled(true);
	GrenadeButton->SetIsEnabled(true);
	GravitonButton->SetIsEnabled(true);
}

void PlayerWidget::SelectCurentWeapon()
{
	if ( dynamic_cast<SimpleGun*>(player->GetWeaponStrategy()) != nullptr)
	{
		SimpleGunButton->bIsSelected = true;	
	}
	else if (dynamic_cast<GrenadeLauncher*>(player->GetWeaponStrategy()) != nullptr)
	{
		GrenadeButton->bIsSelected = true;
	}
}

void PlayerWidget::UpdateAmountOfAmmo()
{
	SimpleGunText->text = std::to_string(player->weapons[0]->currentAmunition) + "/" + std::to_string(player->weapons[0]->munitionInMagazine);
	GrenadeText->text = std::to_string(player->weapons[1]->currentAmunition) + "/" + std::to_string(player->weapons[1]->munitionInMagazine);
	GravitonText->text = std::to_string(player->weapons[2]->currentAmunition) + "/" + std::to_string(player->weapons[2]->munitionInMagazine);
}