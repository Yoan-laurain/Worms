#pragma once

#include "../WeaponStrategy.h"

class SimpleGun : public WeaponStrategy
{
	public:
		SimpleGun();
		~SimpleGun() override;

		/* WeaponStrategy IMPLEMENTATION */
			void DoDamage(SActor* target) override;
			bool Shoot(Level& world, FTransform shootingPoint) override;
		/* END WeaponStrategy IMPLEMENTATION */
	
};