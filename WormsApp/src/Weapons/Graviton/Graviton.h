#pragma once

#include "../WeaponStrategy.h"

class Graviton : WeaponStrategy
{
	public:

		/* WeaponStrategy IMPLEMENTATION */
		void DoDamage(SActor* target) override;
		/* END WeaponStrategy IMPLEMENTATION */
};