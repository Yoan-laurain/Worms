#pragma once

#include "../WeaponStrategy.h"

class GrenadeLauncher : public WeaponStrategy
{
	public:

		GrenadeLauncher();
		~GrenadeLauncher() override;

		/* WeaponStrategy IMPLEMENTATION */
		void DoDamage(SActor* target) override;
		bool Shoot(Level& world, FTransform shootingPoint) override;
		/* END WeaponStrategy IMPLEMENTATION */
};