#include "WormLevel.h"
#include "../Config.h"
#include "../Player/WormsPlayer.h"
#include "../Field/Field.h"
#include <Widgets/Image/ImageWidget.h> 
#include <Library/WidgetHandler.h>

WormLevel::WormLevel() 
	: m_Field(nullptr)
	, WindLogo(nullptr)
	, WindDirection(nullptr)
{
}

void WormLevel::CreatePlayer(const FTransform& SpawnLocation,int PlayerId)
{
	FTransform transform = SpawnLocation;
	transform.Size = FVector2D(25.f, 25.f);
	transform.Location -= transform.Size;

	WormsPlayer* playerPtr = SpawnActor<WormsPlayer>(transform);
	playerPtr->PlayerId = PlayerId;
	playerPtr->Init();

	m_TurnManager->registerObserver(playerPtr);
}

void WormLevel::BeginPlay()
{
	m_TurnManager = std::make_unique<TurnManager>();

	CreateWind();

	FVector2D spawnLocation = FVector2D(Config::WindowWidth / 2, (Config::WindowHeight * 75 ) /100.f);

	m_Field = SpawnActor<Field>(FTransform(spawnLocation, FVector2D(Config::WindowWidth, Config::WindowHeight / 2)));
	m_Field->GenerateFieldCurve();

	for (int i = 0; i < Config::MaxPlayers; ++i)
	{
		CreatePlayer(m_Field->GetSpawnPoint(),i);
	}

	m_TurnManager->nextTurn();
}

void WormLevel::CreateWind()
{
	WindLogo = WidgetHandler::CreateWidget<ImageWidget>(nullptr);
	WindLogo->size = FVector2D(60.f, 40.f);

	int WindowWidth = Config::WindowWidth;
	float SectionForOnePlayer = WindowWidth / Config::MaxPlayers;

	WindLogo->relativePosition = FVector2D(SectionForOnePlayer - WindLogo->size.X / 2.f, 100.f);
	WindLogo->imagePath = "Ressources/Wind.png";
	WindLogo->AddToViewport();

	WindDirection = WidgetHandler::CreateWidget<ImageWidget>(WindLogo);
	WindDirection->size = FVector2D(30.f, 20.f);
	WindDirection->relativePosition = FVector2D(WindLogo->size.X / 2.f - WindDirection->size.X / 2.f, WindLogo->size.Y + 10.f);
	WindDirection->imagePath = "Ressources/WindDirection.png";
	WindDirection->AddToViewport();
}

void WormLevel::UpdateWindDirection(float windDirection)
{
	WindDirection->rotation = windDirection;
}
