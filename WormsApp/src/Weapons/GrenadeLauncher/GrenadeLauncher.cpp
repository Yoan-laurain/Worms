#include "GrenadeLauncher.h"
#include "Grenade/Grenade.h"
#include "../../Player/WormsPlayer.h"
#include <Core/Level.h>

GrenadeLauncher::GrenadeLauncher() : WeaponStrategy(2,80,1)
{
}

void GrenadeLauncher::DoDamage(SActor* Target)
{
	WormsPlayer* Player = dynamic_cast<WormsPlayer*>(Target);
	if (Player)
	{
		Player->OnDamageTaken(Damage);
	}
}

bool GrenadeLauncher::Shoot(Level& World, FTransform ShootingPoint)
{
	if (WeaponStrategy::Shoot(World, ShootingPoint))
	{
		Grenade* MyGrenade = World.SpawnActor<Grenade>(ShootingPoint);
		
		if (MyGrenade)
		{
			MyGrenade->AddForce(FVector2D(1000000, -100000));
			return true;
		}
	}
	return false;
}