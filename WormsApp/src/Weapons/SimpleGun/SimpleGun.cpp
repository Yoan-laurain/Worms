#include "SimpleGun.h"
#include "../../Player/WormsPlayer.h"
#include "Bullet/Bullet.h"
#include <Spoon/Core/Level.h>

SimpleGun::SimpleGun() : WeaponStrategy( 4,50,1)
{
}

void SimpleGun::DoDamage(SActor* Target)
{
	WormsPlayer* MyWormsPlayer = dynamic_cast<WormsPlayer*>(Target);
	
	if (MyWormsPlayer)
	{
		MyWormsPlayer->OnDamageTaken(Damage);
	}
}

bool SimpleGun::Shoot(Level& World, FTransform ShootingPoint)
{
	if (WeaponStrategy::Shoot(World, ShootingPoint))
	{
		Bullet* MyBullet = World.SpawnActor<Bullet>(ShootingPoint);

		if (MyBullet)
		{
			MyBullet->AddForce(FVector2D(10000000, 0.f));
			return true;
		}
	}
	return false;
}