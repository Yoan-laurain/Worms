#include "GrenadeLauncher.h"
#include "Grenade/Grenade.h"
#include "../../Player/WormsPlayer.h"
#include <Core/Level.h>

GrenadeLauncher::GrenadeLauncher() : WeaponStrategy(2,80,1,150.f)
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

bool GrenadeLauncher::Shoot(Level& World, FTransform& ShootingPoint,const FVector2D& Direction)
{
	if (WeaponStrategy::Shoot(World, ShootingPoint,Direction))
	{
		FVector2D Size = FVector2D(30.f, 30.f);
		ShootingPoint.Location.X += Size.X / 2.f;
		
		Grenade* MyGrenade = World.SpawnActor<Grenade>(FTransform(ShootingPoint.Location, Size, 0.f));
		
		if (MyGrenade)
		{
			MyGrenade->AddForce( Direction * BulletSpeed);
			return true;
		}
	}
	return false;
}