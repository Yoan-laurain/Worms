#pragma once

#include "Object/SActor.h"

class WeaponStrategy : public SActor
{
	public:

		WeaponStrategy();

		int currentAmunition;
		int maxAmunition;
		int damage;

		virtual void DoDamage();
		virtual void Reload();
};