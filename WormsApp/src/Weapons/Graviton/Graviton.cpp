#include "Graviton.h"
#include <iostream>

Graviton::Graviton() : WeaponStrategy(1, 100, 1)
{
}

Graviton::~Graviton()
{
}

void Graviton::DoDamage(SActor* target)
{
	std::cout << "Graviton::DoDamage" << std::endl;
}

bool Graviton::Shoot(Level& world, FTransform shootingPoint)
{
    return false;
}
