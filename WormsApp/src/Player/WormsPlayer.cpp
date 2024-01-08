#include "WormsPlayer.h"
#include "../Weapons/WeaponStrategy.h"
#include "../Weapons/SimpleGun/SimpleGun.h"
#include "Objects/Components/SShapeComponent.h"
#include "Objects/Components/SGravityComponent.h"

WormsPlayer::WormsPlayer() :
	currentHealth(100),
	maxHealth(100),
	weaponStrategy(nullptr)
{
	GetPolygonComponent()->texturePath = "Ressources/WormsPlayer.png";
	GetPolygonComponent()->name = "WormsPlayer";

	SetWeaponStrategy( std::make_unique<SimpleGun>() );

	BindFunctionToInputAction(InputAction::Left, std::bind(&WormsPlayer::MoveHorizontal, this, std::placeholders::_1, -1.f));
	BindFunctionToInputAction(InputAction::Right, std::bind(&WormsPlayer::MoveHorizontal, this, std::placeholders::_1, 1.f));

	BindFunctionToInputAction(InputAction::Up, std::bind(&WormsPlayer::MoveVertical, this, std::placeholders::_1, -1.f));
	BindFunctionToInputAction(InputAction::Down, std::bind(&WormsPlayer::MoveVertical, this, std::placeholders::_1, 1.f));
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

		Move(direction * value);
	}
}

void WormsPlayer::MoveHorizontal(float value, float sign)
{
	if (value > 0.f)
	{	
		// TODO : Adapt object to world size
		FVector2D direction = FVector2D(sign * GetSize().X, 0.f);

		Move(direction * value);
	}
}

bool WormsPlayer::OnDamageTaken(int damage)
{
	currentHealth = std::max(0, std::min(currentHealth - damage, maxHealth));

	return currentHealth > 0;
}