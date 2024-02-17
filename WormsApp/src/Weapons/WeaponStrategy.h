#pragma once

#include "Objects/SActor.h"

class WeaponStrategy : public SActor
{
	public:

		WeaponStrategy(int MunitionInMagazine, int Damage, int MunitionByClip, float BulletSpeed);
		WeaponStrategy() = default;

		~WeaponStrategy() override = default;
	
		virtual void DoDamage(SActor* Target);
		virtual void Reload();
		virtual bool Shoot(Level& World, FTransform& ShootingPoint, const FVector2D& Direction);
	
		int CurrentAmmunition;
		int MunitionInMagazine;
		int MunitionByClip;
		int Damage;
		float BulletSpeed;
};