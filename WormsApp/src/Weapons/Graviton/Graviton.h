#pragma once

#include "../WeaponStrategy.h"

// TODO : Implement Graviton weapon
class Graviton : public WeaponStrategy
{
	public:

		Graviton();
		~Graviton() override = default;

		/* WeaponStrategy IMPLEMENTATION */
			void DoDamage(SActor* Target) override;
			bool Shoot(Level& World, FTransform& ShootingPoint,const FVector2D& Direction) override;
		/* END WeaponStrategy IMPLEMENTATION */
};