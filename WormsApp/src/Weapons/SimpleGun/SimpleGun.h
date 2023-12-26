#pragma once

#include "../WeaponStrategy.h"

class SimpleGun : public WeaponStrategy
{
	public:
	
		void DoDamage() override;
};