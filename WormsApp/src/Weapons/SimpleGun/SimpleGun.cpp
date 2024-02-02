#include "SimpleGun.h"
#include <Spoon/Core/Level.h>
#include <iostream>
#include "../Bullet.h"
#include "../../Player/WormsPlayer.h"

SimpleGun::SimpleGun() : WeaponStrategy( 2,50)
{
}

void SimpleGun::DoDamage(SActor* target)
{
	WormsPlayer* wormsPlayer = dynamic_cast<WormsPlayer*>(target);
	wormsPlayer->OnDamageTaken(damage);
}

void SimpleGun::Shoot(Level& world, FTransform shootingPoint)
{
	Bullet* bullet = world.SpawnActor<Bullet>(shootingPoint);

	FVector2D force = FVector2D(10000000, 0.f);

	bullet->AddForce(force);
}