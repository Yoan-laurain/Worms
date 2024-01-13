#include "WormsPlayer.h"
#include "../Weapons/WeaponStrategy.h"
#include "../Weapons/SimpleGun/SimpleGun.h"
#include "Inputs/InputAction.h"
#include "Objects/Components/SShapeComponent.h"

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

void WormsPlayer::SetWeaponStrategy(std::unique_ptr<WeaponStrategy> weaponStrategy)
{
	this->weaponStrategy = std::move(weaponStrategy);
}

void WormsPlayer::onTurnChange(int currentWormsPlayer)
{
	std::cout << "WormsPlayer " << currentWormsPlayer << " is playing" << std::endl;
}

void WormsPlayer::MoveVertical(float value, float sign)
{
	if (value > 0.f)
	{	
		// TODO : Adapt object to world size
		FVector2D direction = FVector2D(0.f, sign * GetSize().Y);

		AddForce(direction * value * 500.f);
	}
}

void WormsPlayer::MoveHorizontal(float value, float sign)
{
	if (value > 0.f)
	{	
		// TODO : Adapt object to world size
		FVector2D direction = FVector2D(sign * GetSize().X, 0.f);

		AddForce(direction * value * 500.f); 
	}
}

void WormsPlayer::ApplyBinding()
{
	BindFunctionToInputAction(InputAction::Left, std::bind(&WormsPlayer::MoveHorizontal, this, std::placeholders::_1, -1.f));
	BindFunctionToInputAction(InputAction::Right, std::bind(&WormsPlayer::MoveHorizontal, this, std::placeholders::_1, 1.f));

	BindFunctionToInputAction(InputAction::Up, std::bind(&WormsPlayer::MoveVertical, this, std::placeholders::_1, -1.f));
	BindFunctionToInputAction(InputAction::Down, std::bind(&WormsPlayer::MoveVertical, this, std::placeholders::_1, 1.f));
}

bool WormsPlayer::OnDamageTaken(int damage)
{
	currentHealth = std::max(0, std::min(currentHealth - damage, maxHealth));

	return currentHealth > 0;
}