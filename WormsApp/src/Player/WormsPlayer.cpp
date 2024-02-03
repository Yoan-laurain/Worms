#include "WormsPlayer.h"
#include "../Weapons/WeaponStrategy.h"
#include "../Weapons/SimpleGun/SimpleGun.h"
#include "Inputs/InputAction.h"
#include "Spoon/Core/Level.h"
#include "Objects/Components/SShapeComponent.h"
#include "../Levels/WormLevel.h"
#include "../Weapons/FragGrenade/GrenadeLauncher.h"
#include <Objects/Prefab/CircleObject.h>
#include <Inputs/InputType.h>

WormsPlayer::WormsPlayer() :
	weaponStrategy(nullptr),
	currentHealth(100),
	maxHealth(100),
	HasShot(false)
{
	GetPolygonComponent()->texturePath = "Ressources/WormsPlayer.png";
	GetPolygonComponent()->name = "WormsPlayer";
	SetDensity(2.f);

	SetWeaponStrategy( std::make_unique<GrenadeLauncher>() );

	ApplyBinding();
}

WormsPlayer::~WormsPlayer()
{
	WormLevel* level = static_cast<WormLevel*>(GetWorld());
	level->m_TurnManager->unregisterObserver(this);	 
}

void WormsPlayer::SetWeaponStrategy(std::unique_ptr<WeaponStrategy> weaponStrategy)
{
	this->weaponStrategy = std::move(weaponStrategy);
}

WeaponStrategy* WormsPlayer::GetWeaponStrategy() const
{
	return weaponStrategy.get();
}

void WormsPlayer::onTurnChange(int currentWormsPlayer)
{
	if (!IsMyTurn())
		return;

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
}

void WormsPlayer::Shoot()
{
	if (!IsMyTurn() || HasShot)
		return;

	HasShot = true;

	FVector2D location = GetLocation();
	location.X += GetForwardVector().X * GetSize().X + 10.f;
	FTransform transform = FTransform(location, FVector2D(5.f, 5.f));

	weaponStrategy->Shoot(*GetWorld(),transform);

	WormLevel* level = static_cast<WormLevel*>(GetWorld());
}

bool WormsPlayer::IsMyTurn()
{
	WormLevel* level = static_cast<WormLevel*>(GetWorld());
	return level->m_TurnManager->currentPlayer == PlayerId;
}

bool WormsPlayer::OnDamageTaken(int damage)
{
	currentHealth = std::max(0, std::min(currentHealth - damage, maxHealth));

	if (currentHealth <= 0)
	{
		MarkActorToDestruction();

		WormLevel* level = dynamic_cast<WormLevel*>(GetWorld());
		level->m_TurnManager->OnEndGame();
	}

	return currentHealth > 0;
}