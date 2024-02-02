#pragma once

#include "Objects/SActor.h"

class WeaponStrategy : public SActor
{
	public:

		WeaponStrategy( int maxAmunition, int damage );

		virtual ~WeaponStrategy() = default;
	
		virtual void DoDamage(SActor* target);
		virtual void Reload();
		virtual void Shoot(Level& world, FTransform shootingPoint);
	
		int currentAmunition;
		int maxAmunition;
		int damage;
};