#include "Grenade.h"
#include "../../../Player/WormsPlayer.h"
#include "../../../Levels/WormLevel.h"

Grenade::Grenade() : NumberOfFragmentsRemaining(0)
{

}

Grenade::~Grenade()
{
	WormLevel* Level = dynamic_cast<WormLevel*>(GetWorld());

	if (Level)
	{
		Level->ATurnManager->NextTurn();
	}
}

void Grenade::OnCollide(SObject* Actor)
{
	if (bIsExploded)
		return;

	LinearVelocity = FVector2D(0, 0);

	NumberOfFragmentsRemaining = NumberOfFragmentsToSpawn;
	bIsExploded = true;
	
	for (int i = -1; i < NumberOfFragmentsToSpawn - 1; i++)
	{
		SpawnFragment(i);
	}
}

void Grenade::SpawnFragment(int FragmentIndex)
{
	FTransform SpawnTransform = GetTransform();
	SpawnTransform.Location.X += FragmentIndex * 100;
	SpawnTransform.Location.Y -= 100.f;

	GrenadeFragment* Fragment = GetWorld()->SpawnActor<GrenadeFragment>(SpawnTransform);

	if (Fragment)
	{
		Fragment->OnFragmentDestroyCallback = std::bind(&Grenade::OnFragmentDestroy, this);

		Fragments.push_back(Fragment);
	}
}

void Grenade::OnFragmentDestroy()
{
	NumberOfFragmentsRemaining--;
	if (NumberOfFragmentsRemaining == 0)
	{
		MarkActorToDestruction();
	}
}

// GrenadeFragment

GrenadeFragment::~GrenadeFragment()
{
	OnFragmentDestroyCallback();
}

void GrenadeFragment::OnCollide(SObject* Actor)
{
	MarkActorToDestruction();

	WormsPlayer* Player = dynamic_cast<WormsPlayer*>(Actor);
	if (Player)
	{
		Player->WeaponStrategy->DoDamage(Player);
	}
}