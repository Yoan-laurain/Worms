#include "GrenadeLauncher.h"
#include "Grenade/Grenade.h"
#include "../../Player/WormsPlayer.h"
#include <Core/Level.h>
#include <iostream>

GrenadeLauncher::GrenadeLauncher() : WeaponStrategy(2,80,1)
{
}

GrenadeLauncher::~GrenadeLauncher()
{
}

void GrenadeLauncher::DoDamage(SActor* target)
{
	WormsPlayer* player = dynamic_cast<WormsPlayer*>(target);
	if (player)
	{
		player->OnDamageTaken(damage);
	}
}

bool GrenadeLauncher::Shoot(Level& world, FTransform shootingPoint)
{
	if (WeaponStrategy::Shoot(world, shootingPoint))
	{
		Grenade* grenade = world.SpawnActor<Grenade>(shootingPoint);
		grenade->AddForce(FVector2D(1000000, -100000));
		return true;
	}

	return false;
}