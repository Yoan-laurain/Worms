#include "Graviton.h"
#include <iostream>

Graviton::Graviton() : WeaponStrategy(1, 100, 1)
{
}

void Graviton::DoDamage(SActor* Target)
{
	std::cout << "Graviton::DoDamage" << std::endl;
}

bool Graviton::Shoot(Level& World, FTransform ShootingPoint)
{
    return false;
}