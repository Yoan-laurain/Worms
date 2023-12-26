#include "WeaponStrategy.h"

WeaponStrategy::WeaponStrategy() : 
	currentAmunition(0),
	maxAmunition(0),
	damage(0)
{
}

void WeaponStrategy::DoDamage()
{
	
}

void WeaponStrategy::Reload()
{
	currentAmunition = maxAmunition;
}