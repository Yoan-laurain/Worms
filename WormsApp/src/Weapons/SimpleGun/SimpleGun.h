#pragma once

#include "../WeaponStrategy.h"

class SimpleGun : public WeaponStrategy
{
	public:

		/* WeaponStrategy IMPLEMENTATION */
			void DoDamage() override;
		/* END WeaponStrategy IMPLEMENTATION */
	
};