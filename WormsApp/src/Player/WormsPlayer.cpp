#include "WormsPlayer.h"
#include "../Weapons/SimpleGun/SimpleGun.h"
#include "../Weapons/Graviton/Graviton.h"
#include "../Weapons/GrenadeLauncher/GrenadeLauncher.h"
#include "../Levels/WormLevel.h"
#include "../Widgets/Player/PlayerWidget.h"
#include "../Config.h"
#include "Controller/WormsPlayerController.h"
#include <Objects/Components/SShapeComponent.h>
#include <Spoon/Core/Level.h>
#include <Core/Application.h>
#include <Library/WidgetHandler.h>

WormsPlayer::WormsPlayer() 
	: PlayerId(0)
	, CurrentHealth(100)
	, MaxHealth(100)
	, bHasShot(false)
	, MyPlayerWidget(nullptr)
	, WeaponStrategy(nullptr)
	, PlayerController(nullptr)
	, bBeenHit(false)
	, HitColor(FColor(255, 0, 0, 255))
	, DefaultColor(FColor::Zero())
	, TimerBeingHit( sf::Clock() )
{
	Weapons.push_back(std::make_shared<SimpleGun>());
	Weapons.push_back(std::make_shared<GrenadeLauncher>());
	Weapons.push_back(std::make_shared<Graviton>());

	WeaponStrategy = Weapons[0];

	PlayerController = new WormsPlayerController();
	PlayerController->Player = this;
	PlayerController->ApplyBinding();
}

WormsPlayer::~WormsPlayer()
{
	WormLevel* Level = dynamic_cast<WormLevel*>(GetWorld());

	if (Level)
	{
		Level->ATurnManager->OnEndGame();
	}

	delete PlayerController;
}

void WormsPlayer::Init()
{
	// TODO : Store the texture path in a config file
	GetPolygonComponent()->TexturePath = PlayerId == 0 ? Config::Player1Right : Config::Player2Right;
	
	CreateHUD();
}

void WormsPlayer::OnTurnChange(int CurrentWormsPlayer)
{
	if (!IsMyTurn())
	{
		MyPlayerWidget->SetWeaponsButtonEnabled(false);
		MyPlayerWidget->DestroyTimer();
		return;
	}

	MyPlayerWidget->SetWeaponsButtonEnabled(true);
	MyPlayerWidget->SelectCurrentWeapon();
	MyPlayerWidget->StartTimer();

	bHasShot = false;
}

void WormsPlayer::SetBeingHit(bool bBeingHit)
{
	this->bBeenHit = bBeingHit;
	TimerBeingHit.restart();
}

void WormsPlayer::CreateHUD()
{
	MyPlayerWidget = WidgetHandler::CreateWidget<PlayerWidget>(nullptr);
	MyPlayerWidget->Player = this;
	MyPlayerWidget->bIsTickable = true;
	MyPlayerWidget->Init();
	MyPlayerWidget->AddToViewport();
}

void WormsPlayer::Tick(float DeltaTime)
{
	SPlayer::Tick(DeltaTime);
	
	if (bBeenHit)
		DisplayHitEffect(DeltaTime);
}

void WormsPlayer::DisplayHitEffect(float DeltaTime)
{
	const float ElapsedTime = TimerBeingHit.getElapsedTime().asSeconds();

	if (fmod(ElapsedTime, 0.2f) <= DeltaTime) // Blink every 0.2 seconds
	{
		GetPolygonComponent()->ObjectColor = GetPolygonComponent()->ObjectColor == DefaultColor ? HitColor : DefaultColor;
	}

	if (ElapsedTime >= 2.f) // Stop Hit Effect after 2 seconds
	{
		SetBeingHit(false);
		GetPolygonComponent()->ObjectColor = DefaultColor;
	}
}

void WormsPlayer::HandlePlayerDeath()
{
	MarkActorToDestruction();

	WormLevel* Level = dynamic_cast<WormLevel*>(GetWorld());
	
	if (Level)
		Level->ATurnManager->OnEndGame();
}

bool WormsPlayer::OnDamageTaken(int Damage)
{
	CurrentHealth = std::max(0.f, std::min(CurrentHealth - Damage, MaxHealth));

	if (MyPlayerWidget)
		MyPlayerWidget->SetHealthBarProgress(CurrentHealth, MaxHealth);

	if (CurrentHealth <= 0)
		HandlePlayerDeath();

	SetBeingHit(true);

	return CurrentHealth > 0;
}

void WormsPlayer::ChangeTurn()
{
	WormLevel* Level = dynamic_cast<WormLevel*>(GetWorld());
	if (Level)
	{
		Level->ATurnManager->NextTurn();
	}
}

bool WormsPlayer::IsMyTurn() const
{
	WormLevel* Level = dynamic_cast<WormLevel*>(GetWorld());
	if (Level)
	{
		return Level->ATurnManager->IsMyTurn(PlayerId);
	}
	return false;
}