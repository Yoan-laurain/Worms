#include "WormsPlayer.h"
#include "../Weapons/WeaponStrategy.h"
#include "../Weapons/SimpleGun/SimpleGun.h"
#include "Objects/Components/SShapeComponent.h"

WormsPlayer::WormsPlayer() :
	currentHealth(100),
	maxHealth(100),
	weaponStrategy(nullptr),
	SpriteComponent(nullptr)
{
	SpriteComponent = CreateComponent<SSpriteComponent>("SpriteComponent");
	SpriteComponent->texturePath = "Ressources/WormsPlayer.png";
	SpriteComponent->name = "WormsPlayer";
	SpriteComponent->Origin = FVector2D(0.f, 0.f);

	SetWeaponStrategy( std::make_unique<SimpleGun>() );
	std::cout << GetClassName() << std::endl;

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
	FVector2D direction = FVector2D(0.f, sign);
	FVector2D location = GetLocation();

	SetLocation(location + direction * value);
}

void WormsPlayer::MoveHorizontal(float value, float sign)
{
	FVector2D direction = FVector2D(sign, 0.f);
	FVector2D location = GetLocation();

	SetLocation(location + direction * value);
}

bool WormsPlayer::OnDamageTaken(int damage)
{
	currentHealth = std::max(0, std::min(currentHealth - damage, maxHealth));

	return currentHealth > 0;
}