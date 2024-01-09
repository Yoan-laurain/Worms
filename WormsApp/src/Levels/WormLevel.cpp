#include "WormLevel.h"
#include "../Config.h"
#include "../Player/WormsPlayer.h"
#include "Objects/Prefab/CircleObject.h"
#include "Objects/Prefab/PolygonObject.h"
#include "Objects/Components/SShapeComponent.h"

void WormLevel::CreatePlayer(FTransform& SpawnLocation)
{
	FTransform transform = SpawnLocation;
	transform.Size = FVector2D(50.f, 50.f);
	transform.Location += transform.Size / 2.f;

	WormsPlayer* playerPtr = SpawnActor<WormsPlayer>(transform);
	playerPtr->GetPolygonComponent()->Points = {FVector2D(-25, -25), FVector2D(25, -25), FVector2D(25, 25), FVector2D(-25, 25)};

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
		FTransform transform;
		transform.Location = FVector2D(100, 100);
		CreatePlayer( transform );

		SPolygonObject* polygon = SpawnActor<SPolygonObject>(FTransform(FVector2D(250, 100), FVector2D(50, 50)));
		std::vector<FVector2D> points; 
		points.push_back(FVector2D(-25, -25));
		points.push_back(FVector2D( 25, -25));
		points.push_back(FVector2D( 25, 25));
		points.push_back(FVector2D(-25, 25)); 
		polygon->GetPolygonComponent()->Points = points; 
		polygon->bIsStatic = true;

		SpawnActor<SCircleObject>(FTransform(FVector2D(305, 100), FVector2D(50, 50))); 
		//SpawnActor<SCircleObject>(FTransform(FVector2D(350, 100), FVector2D(50, 50))); 
		 
	}
}