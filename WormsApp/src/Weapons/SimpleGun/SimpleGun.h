#pragma once

#include "../WeaponStrategy.h"

class SimpleGun : public WeaponStrategy
{
	public:
		SimpleGun();
		~SimpleGun() override = default;

		/* WeaponStrategy IMPLEMENTATION */
			void DoDamage(SActor* Target) override;
			bool Shoot(Level& World, FTransform& ShootingPoint,const FVector2D& Direction) override;
		/* END WeaponStrategy IMPLEMENTATION */
};