#include "WormLevel.h"
#include "../Config.h"
#include "../Player/WormsPlayer.h"

void WormLevel::CreatePlayer()
{
	WormsPlayer* playerPtr = SpawnActor<WormsPlayer>(FTransform(FVector2D(50,50), FVector2D(50, 50))); // TODO : Adapt SpawnLocation
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