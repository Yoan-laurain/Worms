#include "GrenadeLauncher.h"
#include "Grenade/Grenade.h"
#include <Core/Level.h>
#include <iostream>

GrenadeLauncher::GrenadeLauncher() : WeaponStrategy(2,80)
{
}

void GrenadeLauncher::DoDamage(SActor* target)
{
}

void GrenadeLauncher::Shoot(Level& world, FTransform shootingPoint)
{
	Grenade* grenade = world.SpawnActor<Grenade>(shootingPoint);
	grenade->AddForce(FVector2D(1000000, -100000));
}