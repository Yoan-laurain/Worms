#include "WormLevel.h"
#include "../Config.h"
#include "../Player/WormsPlayer.h"
#include "Objects/Prefab/RectangleObject.h"
#include "Objects/Prefab/CircleObject.h"

void WormLevel::CreatePlayer(FTransform& SpawnLocation)
{
	FTransform transform = SpawnLocation;
	transform.Size = FVector2D(50.f, 50.f);
	transform.Location.Y -= transform.Size.Y;
	transform.Rotation = 0.f;

	WormsPlayer* playerPtr = SpawnActor<WormsPlayer>(transform);

	m_TurnManager->registerObserver(playerPtr);
}

void WormLevel::BeginPlay()
{
	m_TurnManager = std::make_unique<TurnManager>();

	//m_Field = SpawnActor<Field>(FTransform());
	//m_Field->GenerateFieldCurve();

	for (int i = 0; i < Config::MaxPlayers; ++i)
	{
		//CreatePlayer(m_Field->GetSpawnPoint());
		SpawnActor<SRectangleObject>(FTransform(FVector2D(50 * (i + 1), 50 * (1 + i)), FVector2D(50, 50)));
		SpawnActor<SCircleObject>(FTransform(FVector2D( 250 * (i + 1), 250 * (1 + i)), FVector2D(50, 50)));
	}
}