#pragma once

#include "Objects/SActor.h"

class WeaponStrategy : public SActor
{
	public:

		WeaponStrategy(int munitionInMagazine, int damage, int munitionByClip);
		WeaponStrategy() = default;

		virtual ~WeaponStrategy() = default;
	
		virtual void DoDamage(SActor* target);
		virtual void Reload();
		virtual bool Shoot(Level& world, FTransform shootingPoint);
	
		int currentAmunition;
		int munitionInMagazine;
		int munitionByClip;
		int damage;
};