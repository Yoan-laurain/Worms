#include "WormLevel.h"
#include "../Player/Player.h"
#include "../Config.h"

void WormLevel::CreatePlayer()
{
	std::shared_ptr<Player> playerPtr = SpawnActor<Player>(FTransform(FVector2D(0, 0), FVector2D(1, 1))); // TODO : Adapt SpawnLocation
	m_TurnManager->registerObserver(playerPtr);
}

void WormLevel::BeginPlay()
{
	m_TurnManager = std::make_unique<TurnManager>();

    for (int i = 0; i < Config::MaxPlayers; ++i)
    {
		CreatePlayer();
	}

	m_Field = SpawnActor<Field>(FTransform());
	m_Field->GenerateFieldCurve();
}