#include "WormsPlayer.h"
#include "../Weapons/WeaponStrategy.h"
#include "../Weapons/SimpleGun/SimpleGun.h"
#include "Inputs/InputAction.h"
#include "Spoon/Core/Level.h"
#include "Objects/Components/SShapeComponent.h"
#include "../Weapons/FragGrenade/GrenadeLauncher.h"
#include "../Weapons/Graviton/Graviton.h"
#include "../Levels/WormLevel.h"
#include "PlayerWidget.h"
#include <Inputs/InputType.h>
#include <Core/Application.h>
#include <Library/WidgetHandler.h>

WormsPlayer::WormsPlayer() :
	currentHealth(100),
	weaponStrategy(nullptr),
	maxHealth(100),
	HasShot(false)
{
	SetDensity(2.f);

	weapons.push_back(std::make_shared<SimpleGun>());
	weapons.push_back(std::make_shared<GrenadeLauncher>());
	weapons.push_back(std::make_shared<Graviton>());

	SetWeaponStrategy( weapons[0] );

	ApplyBinding();
}

WormsPlayer::~WormsPlayer()
{
	WormLevel* level = static_cast<WormLevel*>(GetWorld());
	level->m_TurnManager->unregisterObserver(this);	 
}

void WormsPlayer::SetWeaponStrategy(std::shared_ptr<WeaponStrategy> weapon)
{
	this->weaponStrategy = weapon;
}

WeaponStrategy* WormsPlayer::GetWeaponStrategy() const
{
	return weaponStrategy.get();
}

void WormsPlayer::onTurnChange(int currentWormsPlayer)
{
	if (!IsMyTurn())
	{
		playerWidget->DisableWidget();
		playerWidget->DestroyTimer();
		return;
	}

	playerWidget->EnableWidget();
	playerWidget->SelectCurentWeapon();
	playerWidget->StartTimer();

	HasShot = false;
}

void WormsPlayer::MoveVertical(float value, float sign)
{
	if (!IsMyTurn() || HasShot)
		return;
	
	if (value > 0.f)
	{	
		// TODO : Adapt object to world size
		FVector2D direction = FVector2D(0.f, sign * GetSize().Y);

		AddForce(direction * value * 500.f);
	}
}

void WormsPlayer::MoveHorizontal(float value, float sign)
{
	if (!IsMyTurn() || HasShot)
		return;

	if (value > 0.f)
	{	
		// TODO : Adapt object to world size
		FVector2D direction = FVector2D(sign * GetSize().X, 0.f);

		AddForce(direction * value * 500.f); 
	}
}

void WormsPlayer::ApplyBinding()
{
	BindFunctionToInputAction(InputAction::Left, std::bind(&WormsPlayer::MoveHorizontal, this, std::placeholders::_1, -1.f),InputType::Hold);
	BindFunctionToInputAction(InputAction::Right, std::bind(&WormsPlayer::MoveHorizontal, this, std::placeholders::_1, 1.f), InputType::Hold);

	BindFunctionToInputAction(InputAction::Up, std::bind(&WormsPlayer::MoveVertical, this, std::placeholders::_1, -1.f), InputType::Hold);
	BindFunctionToInputAction(InputAction::Down, std::bind(&WormsPlayer::MoveVertical, this, std::placeholders::_1, 1.f), InputType::Hold);

	BindFunctionToInputAction(InputAction::Fire, std::bind(&WormsPlayer::Shoot, this), InputType::Pressed);
	BindFunctionToInputAction(InputAction::Reload, std::bind(&WormsPlayer::Reload, this), InputType::Pressed);
}

void WormsPlayer::Shoot()
{
	if (!IsMyTurn() || HasShot)
		return;

	FVector2D location = GetLocation();
	location.X += GetForwardVector().X * GetSize().X + 10.f;
	FTransform transform = FTransform(location, FVector2D(5.f, 5.f));

	if (weaponStrategy->Shoot(*GetWorld(), transform))
	{
		HasShot = true;
		playerWidget->UpdateAmountOfAmmo(); 
		playerWidget->StopTimer();
	}
}

bool WormsPlayer::IsMyTurn()
{
	WormLevel* level = static_cast<WormLevel*>(GetWorld());
	return level->m_TurnManager->currentPlayer == PlayerId;
}

void WormsPlayer::Reload()
{
	if (!IsMyTurn() || HasShot)
		return;

	weaponStrategy->Reload(); 
	playerWidget->UpdateAmountOfAmmo(); 
}

void WormsPlayer::CreateHUD()
{
	playerWidget = WidgetHandler::CreateWidget<PlayerWidget>(nullptr);
	playerWidget->player = this;
	playerWidget->bIsTickable = true;
	playerWidget->Init();
	playerWidget->AddToViewport();
}

bool WormsPlayer::OnDamageTaken(int damage)
{
	currentHealth = std::max(0.f, std::min(currentHealth - damage, maxHealth));

	if (playerWidget)
	{
		playerWidget->SetHealthBarProgress(currentHealth, maxHealth);
	}

	if (currentHealth <= 0)
	{
		MarkActorToDestruction();

		WormLevel* level = dynamic_cast<WormLevel*>(GetWorld());
		level->m_TurnManager->OnEndGame();
	}

	return currentHealth > 0;
}

void WormsPlayer::Init()
{
	GetPolygonComponent()->name = "WormsPlayer " + std::to_string(PlayerId);
	GetPolygonComponent()->texturePath = PlayerId == 0 ? "Ressources/WormsPlayer.png" : "Ressources/WormsPlayer2.png";

	CreateHUD();
}

void WormsPlayer::ChangeTurn()
{
	dynamic_cast<WormLevel*>(GetWorld())->m_TurnManager->nextTurn();
}