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
	//transform.Location.Y -= transform.Size.Y;
	transform.Rotation = 0.f;

	WormsPlayer* playerPtr = SpawnActor<WormsPlayer>(transform);
	playerPtr->GetPolygonComponent()->Points = {FVector2D(-50, -50), FVector2D(50, -50), FVector2D(50, 50), FVector2D(-50, 50)};

	m_TurnManager->registerObserver(playerPtr);
}

void WormLevel::BeginPlay()
{
	m_TurnManager = std::make_unique<TurnManager>();

	m_Field = SpawnActor<Field>(FTransform( FVector2D(Config::WindowWidth / 2, Config::WindowHeight), FVector2D(Config::WindowWidth, Config::WindowHeight / 2)));
	m_Field->GenerateFieldCurve();

	for (int i = 0; i < Config::MaxPlayers; ++i)
	{
		//CreatePlayer(m_Field->GetSpawnPoint());
		FTransform transform = FTransform(FTransform(FVector2D(200, 100), FVector2D(50, 50)));
		CreatePlayer(transform);

		SPolygonObject* polygon = SpawnActor<SPolygonObject>(FTransform(FVector2D(400, 100), FVector2D(50, 50)));
		std::vector<FVector2D> points; 
		points.push_back(FVector2D(-50, -50));
		points.push_back(FVector2D( 50, -50));
		points.push_back(FVector2D( 50, 50));
		points.push_back(FVector2D(-50, 50)); 
		polygon->GetPolygonComponent()->Points = points; 

		SpawnActor<SCircleObject>(FTransform(FVector2D(600, 100), FVector2D(50, 50))); // bug here 
		SpawnActor<SCircleObject>(FTransform(FVector2D(800, 100), FVector2D(50, 50))); // bug here 
		 
	}
}