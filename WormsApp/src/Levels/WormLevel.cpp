#include "WormLevel.h"
#include "../Player/Player.h"
#include "../Config.h"

void WormLevel::CreatePlayer()
{
	Player* player = SpawnActor<Player>(FTransform(FVector2D(0, 0), FVector2D(1, 1))); // TODO : Adapt SpawnLocation

	// TODO ! Fix le crash du moteur shared_ptr
	//std::shared_ptr<Player> playerPtr(player);
	//m_TurnManager->registerObserver(playerPtr);
}

void WormLevel::BeginPlay()
{
	m_TurnManager = std::make_unique<TurnManager>();

    for (int i = 0; i < Config::MaxPlayers; ++i)
    {
		CreatePlayer();
	}

	m_Field = std::make_unique<Field>();
	m_Field->SetWorldRef(this);
	m_Field->GenerateFieldCurve();
}