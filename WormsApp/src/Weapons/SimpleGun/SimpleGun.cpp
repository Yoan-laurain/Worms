#include "SimpleGun.h"
#include "../../Player/WormsPlayer.h"
#include "Bullet/Bullet.h"
#include <Spoon/Core/Level.h>
#include <iostream>

SimpleGun::SimpleGun() : WeaponStrategy( 4,50,1)
{
}

SimpleGun::~SimpleGun()
{
}

void SimpleGun::DoDamage(SActor* target)
{
	WormsPlayer* wormsPlayer = dynamic_cast<WormsPlayer*>(target);
	wormsPlayer->OnDamageTaken(damage);
}

bool SimpleGun::Shoot(Level& world, FTransform shootingPoint)
{
	if (WeaponStrategy::Shoot(world, shootingPoint))
	{
		Bullet* bullet = world.SpawnActor<Bullet>(shootingPoint);

		FVector2D force = FVector2D(10000000, 0.f);

		bullet->AddForce(force);

		return true;
	}
	return false;
}