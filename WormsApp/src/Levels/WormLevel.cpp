#include "WormLevel.h"
#include "../Config.h"
#include "../Player/WormsPlayer.h"
#include "Objects/Prefab/CircleObject.h"

void WormLevel::CreatePlayer(FTransform& SpawnLocation)
{
	FTransform transform = SpawnLocation;
	transform.Size = FVector2D(50.f, 50.f);
	transform.Location.Y -= transform.Size.Y;

	WormsPlayer* playerPtr = SpawnActor<WormsPlayer>(transform);

	m_TurnManager->registerObserver(playerPtr);
}

void WormLevel::BeginPlay()
{
	m_TurnManager = std::make_unique<TurnManager>();

	m_Field = SpawnActor<Field>(FTransform());
	m_Field->GenerateFieldCurve();

	for (int i = 0; i < Config::MaxPlayers; ++i)
	{
		CreatePlayer(m_Field->GetSpawnPoint());
	}
}