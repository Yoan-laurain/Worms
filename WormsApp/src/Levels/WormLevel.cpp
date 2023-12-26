#include "WormLevel.h"
#include "../Turn/TurnManager.h"
#include "../Player/Player.h"

void WormLevel::CreatePlayer()
{
	Player* player = SpawnActor<Player>(FTransform(FVector2D(0, 0), FVector2D(1, 1))); // TODO : Adapt SpawnLocation

	std::shared_ptr<Player> playerPtr(player);

	m_TurnManager->registerObserver(playerPtr);
}

void WormLevel::BeginPlay()
{
	m_TurnManager = std::make_unique<TurnManager>();

    int nbPlayers = 2;

    for (int i = 0; i < nbPlayers; i++)
    {
		CreatePlayer();
	}
}