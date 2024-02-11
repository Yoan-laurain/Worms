#pragma once

#include "../WeaponStrategy.h"

class Graviton : public WeaponStrategy
{
	public:

		Graviton();
		~Graviton() override;

		/* WeaponStrategy IMPLEMENTATION */
			void DoDamage(SActor* target) override;
			bool Shoot(Level& world, FTransform shootingPoint) override;
		/* END WeaponStrategy IMPLEMENTATION */
};