#include "WeaponStrategy.h"
#include <Library/MathLibrary.h>


WeaponStrategy::WeaponStrategy(int munitionInMagazine, int damage, int munitionByClip)
	: munitionInMagazine(munitionInMagazine)
	, damage(damage)
	, currentAmunition(munitionByClip)
	, munitionByClip(munitionByClip)
{
}

void WeaponStrategy::DoDamage(SActor* target)
{
	
}

void WeaponStrategy::Reload()
{
	if (currentAmunition == munitionByClip)
	{
		return;
	}

	munitionInMagazine = MathLibrary::Clamp(munitionInMagazine - munitionByClip, 0, munitionInMagazine);
	currentAmunition = MathLibrary::Clamp(munitionInMagazine, 0, munitionByClip);
}

bool WeaponStrategy::Shoot(Level& world, FTransform shootingPoint)
{
	if (currentAmunition > 0)
	{
		currentAmunition--;
		return true;
	}

	return false;
}
