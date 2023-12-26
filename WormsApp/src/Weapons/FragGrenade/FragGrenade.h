#pragma once

#include "../WeaponStrategy.h"

class FragGrenade : public WeaponStrategy
{
	public:
	
		void DoDamage() override;
};