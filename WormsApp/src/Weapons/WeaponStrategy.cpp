#include "WeaponStrategy.h"


WeaponStrategy::WeaponStrategy(int maxAmunition, int damage) : maxAmunition(maxAmunition), damage(damage), currentAmunition(maxAmunition)
{
}

void WeaponStrategy::DoDamage(SActor* target)
{
	
}

void WeaponStrategy::Reload()
{
	currentAmunition = maxAmunition;
}

void WeaponStrategy::Shoot(Level& world, FTransform shootingPoint)
{
	if (currentAmunition > 0)
	{
		currentAmunition--;
	}
	else
	{
		Reload();
	}
}
