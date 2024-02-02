#include "WormsPlayer.h"
#include "../Weapons/WeaponStrategy.h"
#include "../Weapons/SimpleGun/SimpleGun.h"
#include "Inputs/InputAction.h"
#include "Spoon/Core/Level.h"
#include "Objects/Components/SShapeComponent.h"
#include <Objects/Prefab/CircleObject.h>
#include "../Levels/WormLevel.h"

WormsPlayer::WormsPlayer() :
	weaponStrategy(nullptr),
	currentHealth(100),
	maxHealth(100)
{
	GetPolygonComponent()->texturePath = "Ressources/WormsPlayer.png";
	GetPolygonComponent()->name = "WormsPlayer";
	SetDensity(2.f);

	SetWeaponStrategy( std::make_unique<SimpleGun>() );

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
	
}

void WormsPlayer::MoveVertical(float value, float sign)
{
	if (!IsMyTurn())
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
	if (!IsMyTurn())
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
	if (!IsMyTurn())
	{
		std::cout << "Not my turn to shoot as player " << PlayerId << std::endl;
		return;
	}
	else
{
		std::cout << "My turn to shoot as player " << PlayerId << std::endl;
	}

	FVector2D location = GetLocation();
	location.X += GetForwardVector().X * GetSize().X + 10.f;
	FTransform transform = FTransform(location, FVector2D(5.f, 5.f));

	weaponStrategy->Shoot(*GetWorld(),transform);

	WormLevel* level = static_cast<WormLevel*>(GetWorld());
}

bool WormsPlayer::IsMyTurn()
{
	WormLevel* level = static_cast<WormLevel*>(GetWorld());
	std::cout << "Current player : " << level->m_TurnManager->currentPlayer << " - My player : " << PlayerId << std::endl;
	return level->m_TurnManager->currentPlayer == PlayerId;
}

bool WormsPlayer::OnDamageTaken(int damage)
{
	currentHealth = std::max(0, std::min(currentHealth - damage, maxHealth));

	if (currentHealth <= 0)
	{
		MarkActorToDestruction();
	}

	return currentHealth > 0;
}