#include "SimpleGun.h"
#include "../../Player/WormsPlayer.h"
#include "Bullet/Bullet.h"
#include <Spoon/Core/Level.h>
#include <Objects/Components/SShapeComponent.h>

SimpleGun::SimpleGun()
	: WeaponStrategy( 4,50,1, 200.f)
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

bool SimpleGun::Shoot(Level& World,FTransform& ShootingPoint,const FVector2D& Direction)
{
	if (WeaponStrategy::Shoot(World, ShootingPoint,Direction))
	{
		FVector2D Size = FVector2D(30.f, 30.f);
		ShootingPoint.Location.X += Size.X / 2.f;
		
		Bullet* MyBullet = World.SpawnActor<Bullet>(FTransform(ShootingPoint.Location, Size, 0.f));

		if (MyBullet)
		{
			MyBullet->AddForce(Direction * BulletSpeed);
			return true;
		}
	}
	return false;
}