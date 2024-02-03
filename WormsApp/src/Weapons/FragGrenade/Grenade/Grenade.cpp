#include "Grenade.h"
#include "../../../Player/WormsPlayer.h"
#include "../../../Levels/WormLevel.h"

Grenade::Grenade() : NumberOfFragmentsToSpawn(3), fragments(), NumberOfFragmentsRemaining(0)
{

}

Grenade::~Grenade()
{
	WormLevel* level = dynamic_cast<WormLevel*>(GetWorld());
	level->m_TurnManager->nextTurn();
}

void Grenade::OnCollide(Manifold& contact)
{
	if (bIsExploded)
		return;

	LinearVelocity = FVector2D(0, 0);

	NumberOfFragmentsRemaining = NumberOfFragmentsToSpawn;
	bIsExploded = true;
	for (int i = -1; i < NumberOfFragmentsToSpawn - 1; i++)
	{
		FTransform spawnTransform = GetTransform();
		spawnTransform.Location.X += i * 100;
		spawnTransform.Location.Y -= 100.f;

		GrenadeFragment* fragment = GetWorld()->SpawnActor<GrenadeFragment>(spawnTransform);

		fragment->OnFragmentDestroyCallback = std::bind(&Grenade::OnFragmentDestroy, this);

		fragments.push_back(fragment);
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

GrenadeFragment::GrenadeFragment()
{
}

GrenadeFragment::~GrenadeFragment()
{
	OnFragmentDestroyCallback();
}

void GrenadeFragment::OnCollide(Manifold& contact)
{
	MarkActorToDestruction();

	if (contact.BodyA)
	{
		WormsPlayer* player = dynamic_cast<WormsPlayer*>(contact.BodyA);
		if (player && contact.BodyB)
		{
			player->GetWeaponStrategy()->DoDamage(player);
		}
	}
}