#include "WeaponStrategy.h"
#include <Library/MathLibrary.h>

WeaponStrategy::WeaponStrategy(int MunitionInMagazine, int Damage, int MunitionByClip, float BulletSpeed)
	: CurrentAmmunition(MunitionByClip)
	, MunitionInMagazine(MunitionInMagazine)
	, MunitionByClip(MunitionByClip)
    , Damage(Damage)
	, BulletSpeed(BulletSpeed)
{
}

void WeaponStrategy::DoDamage(SActor* Target)
{
	
}

void WeaponStrategy::Reload()
{
	if (CurrentAmmunition == MunitionByClip)
	{
		return;
	}

	MunitionInMagazine = MathLibrary::Clamp(MunitionInMagazine - MunitionByClip, 0, MunitionInMagazine);
	CurrentAmmunition = MathLibrary::Clamp(MunitionInMagazine, 0, MunitionByClip);
}

bool WeaponStrategy::Shoot(Level& World, FTransform& ShootingPoint,const FVector2D& Direction)
{
	if (CurrentAmmunition > 0)
	{
		CurrentAmmunition--;
		return true;
	}

	return false;
}