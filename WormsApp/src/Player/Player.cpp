#include "Player.h"
#include "../Weapons/WeaponStrategy.h"
#include "../Weapons/SimpleGun/SimpleGun.h"

Player::Player() :
	currentHealth(100),
	maxHealth(100),
	weaponStrategy(nullptr)
{
	SetWeaponStrategy( std::make_unique<SimpleGun>() );
}

void Player::SetWeaponStrategy(std::unique_ptr<WeaponStrategy> weaponStrategy)
{
	this->weaponStrategy = std::move(weaponStrategy);
}

void Player::onTurnChange(int currentPlayer)
{
	std::cout << "Player " << currentPlayer << " is playing" << std::endl;
}

bool Player::OnDamageTaken(int damage)
{
	currentHealth = std::max(0, std::min(currentHealth - damage, maxHealth));

	return currentHealth > 0;
}