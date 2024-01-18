#include "WormLevel.h"
#include "../Config.h"
#include "../Player/WormsPlayer.h"
#include "../Field/Field.h"

WormLevel::WormLevel() : m_Field(nullptr)
{
}

void WormLevel::CreatePlayer(const FTransform& SpawnLocation)
{
	FTransform transform = SpawnLocation;
	transform.Size = FVector2D(50.f, 50.f);
	transform.Location += transform.Size / 2.f;

	WormsPlayer* playerPtr = SpawnActor<WormsPlayer>(transform);

	m_TurnManager->registerObserver(playerPtr);
}

void WormLevel::BeginPlay()
{
	m_TurnManager = std::make_unique<TurnManager>();

	FVector2D spawnLocation = FVector2D(Config::WindowWidth / 2, (Config::WindowHeight * 75 ) /100.f);

	m_Field = SpawnActor<Field>(FTransform(spawnLocation, FVector2D(Config::WindowWidth, Config::WindowHeight / 2)));
	m_Field->GenerateFieldCurve();

	for (int i = 0; i < Config::MaxPlayers; ++i)
	{
		//CreatePlayer(m_Field->GetSpawnPoint());
	}
}