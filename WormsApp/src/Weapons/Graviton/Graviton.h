#pragma once

#include "../WeaponStrategy.h"

class Graviton : WeaponStrategy
{
	public:

		/* WeaponStrategy IMPLEMENTATION */
		void DoDamage() override;
		/* END WeaponStrategy IMPLEMENTATION */
};