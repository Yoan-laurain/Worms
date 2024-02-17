#include "Grenade.h"
#include "../../../Config.h"
#include "../../../Player/WormsPlayer.h"
#include "../../../Levels/WormLevel.h"
#include "Objects/Components/SShapeComponent.h"

Grenade::Grenade() 
{
	GetComponent<SShapeComponent>()->TexturePath = Config::Grenade;
}

void Grenade::OnCollide(SObject* Actor)
{
	if (bIsExploded)
		return;

	LinearVelocity = FVector2D(0, 0);

	WormsPlayer* Player = dynamic_cast<WormsPlayer*>(Actor);
	if (Player)
	{
		Player->WeaponStrategy->DoDamage(Player);
	}

	WormLevel* Level = dynamic_cast<WormLevel*>(GetWorld());

	if (Level)
		Level->NumberOfGrenadeFragmentsRemaining = NumberOfFragmentsToSpawn;
	
	bIsExploded = true;
	
	for (int i = -1; i < NumberOfFragmentsToSpawn - 1; i++)
	{
		SpawnFragment(i);
	}
	
	MarkActorToDestruction();
}

void Grenade::SpawnFragment(int FragmentIndex)
{
	FTransform SpawnTransform = GetTransform();
	SpawnTransform.Location.X += FragmentIndex * 100;
	SpawnTransform.Location.Y -= 100.f; 

	GrenadeFragment* Fragment = GetWorld()->SpawnActor<GrenadeFragment>(SpawnTransform);

	if (Fragment)
	{
		WormLevel* Level = dynamic_cast<WormLevel*>(GetWorld());
		
		if (Level)
		{
			Fragment->OnFragmentDestroyCallback = std::bind(&WormLevel::OnGrenadeFragmentDestroy, Level); 
			Level->GrenadeFragments.push_back(Fragment); 
		}
	}
}

// GrenadeFragment

GrenadeFragment::GrenadeFragment()
{
	GetComponent<SShapeComponent>()->TexturePath = Config::GrenadePieces; 
}

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