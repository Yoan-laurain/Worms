#pragma once

#include "../WeaponStrategy.h"

class FragGrenade : public WeaponStrategy
{
	public:

		/* WeaponStrategy IMPLEMENTATION */
		void DoDamage() override;
		/* END WeaponStrategy IMPLEMENTATION */
};