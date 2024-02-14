#pragma once

#include "../WeaponStrategy.h"

class SimpleGun : public WeaponStrategy
{
	public:
		SimpleGun();
		~SimpleGun() override = default;

		/* WeaponStrategy IMPLEMENTATION */
			void DoDamage(SActor* Target) override;
			bool Shoot(Level& World, FTransform ShootingPoint) override;
		/* END WeaponStrategy IMPLEMENTATION */
	
};