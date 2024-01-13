#pragma once

#include "Objects/SActor.h"

class WeaponStrategy : public SActor
{
	public:

		WeaponStrategy();

		virtual ~WeaponStrategy() = default;
	
		virtual void DoDamage();
		virtual void Reload();
	
		int currentAmunition;
		int maxAmunition;
		int damage;
};