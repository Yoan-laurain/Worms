#include "WormLevel.h"
#include "../Turn/TurnManager.h"
#include "../Player/Player.h"

void WormLevel::CreatePlayer( TurnManager& turnManager )
{
	Player* player = SpawnActor<Player>(FTransform( FVector2D( 0, 0), FVector2D(1, 1) )); // TODO : Adapt SpawnLocation

	std::shared_ptr<Player> playerPtr(player);

	turnManager.registerObserver(playerPtr);
}

void WormLevel::BeginPlay()
{
    TurnManager turnManager;

    int nbPlayers = 2;

    for (int i = 0; i < nbPlayers; i++)
    {
		CreatePlayer(turnManager);
	}
}