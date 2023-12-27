#include "WormLevel.h"
#include "../Player/Player.h"
#include "../Config.h"

void WormLevel::CreatePlayer()
{
	std::shared_ptr<Player> playerPtr = SpawnActor<Player>(FTransform(FVector2D(50, 50), FVector2D(50, 50))); // TODO : Adapt SpawnLocation
	m_TurnManager->registerObserver(playerPtr);
}

void WormLevel::BeginPlay()
{
	m_TurnManager = std::make_unique<TurnManager>();

    for (int i = 0; i < Config::MaxPlayers; ++i)
    {
		SpawnActor<Player>(FTransform(FVector2D(50 * i, 50 * i), FVector2D(50, 50))); // TODO : Adapt SpawnLocation

	}

	m_Field = SpawnActor<Field>(FTransform());
	m_Field->GenerateFieldCurve();
}