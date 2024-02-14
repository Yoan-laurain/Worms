#pragma once

#include "../WeaponStrategy.h"

class GrenadeLauncher : public WeaponStrategy
{
	public:

		GrenadeLauncher();
		~GrenadeLauncher() override = default;

		/* WeaponStrategy IMPLEMENTATION */
		void DoDamage(SActor* Target) override;
		bool Shoot(Level& World, FTransform ShootingPoint) override;
		/* END WeaponStrategy IMPLEMENTATION */
};