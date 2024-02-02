#pragma once

#include "../WeaponStrategy.h"

class FragGrenade : public WeaponStrategy
{
	public:

		/* WeaponStrategy IMPLEMENTATION */
		void DoDamage(SActor* target) override;
		/* END WeaponStrategy IMPLEMENTATION */
};