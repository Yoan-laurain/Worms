#pragma once

#include "../WeaponStrategy.h"

class GrenadeLauncher : public WeaponStrategy
{
	public:

		GrenadeLauncher();
		~GrenadeLauncher() override = default;

		/* WeaponStrategy IMPLEMENTATION */
		void DoDamage(SActor* Target) override;
		bool Shoot(Level& World, FTransform& ShootingPoint,const FVector2D& Direction) override;
		/* END WeaponStrategy IMPLEMENTATION */
};