#include "WormLevel.h"
#include "../Config.h"
#include "../Player/WormsPlayer.h"
#include "Objects/Prefab/CircleObject.h"

void WormLevel::CreatePlayer()
{
	WormsPlayer* playerPtr = SpawnActor<WormsPlayer>(FTransform(FVector2D(50,50), FVector2D(20, 20))); // TODO : Adapt SpawnLocation
	m_TurnManager->registerObserver(playerPtr);
}

void WormLevel::BeginPlay()
{
	m_TurnManager = std::make_unique<TurnManager>();

    for (int i = 0; i < Config::MaxPlayers; ++i)
    {
		CreatePlayer();
		// SpawnActor<SCircleObject>(FTransform(FVector2D(50*(i+1), 50* (1+i)), FVector2D(20, 20))); // TODO : Adapt SpawnLocation
	}

	m_Field = SpawnActor<Field>(FTransform());
	m_Field->GenerateFieldCurve();
}