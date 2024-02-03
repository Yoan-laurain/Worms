#pragma once

#include "../WeaponStrategy.h"

class GrenadeLauncher : public WeaponStrategy
{
	public:

		GrenadeLauncher();

		/* WeaponStrategy IMPLEMENTATION */
		void DoDamage(SActor* target) override;
		virtual void Shoot(Level& world, FTransform shootingPoint) override;
		/* END WeaponStrategy IMPLEMENTATION */
};