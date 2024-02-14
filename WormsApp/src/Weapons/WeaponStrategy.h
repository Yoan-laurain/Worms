#pragma once

#include "Objects/SActor.h"

class WeaponStrategy : public SActor
{
	public:

		WeaponStrategy(int MunitionInMagazine, int Damage, int MunitionByClip);
		WeaponStrategy() = default;

		~WeaponStrategy() override = default;
	
		virtual void DoDamage(SActor* Target);
		virtual void Reload();
		virtual bool Shoot(Level& World, FTransform ShootingPoint);
	
		int CurrentAmmunition;
		int MunitionInMagazine;
		int MunitionByClip;
		int Damage;
};