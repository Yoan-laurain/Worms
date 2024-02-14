#include "WormLevel.h"
#include "../Config.h"
#include "../Player/WormsPlayer.h"
#include "../Widgets/Wind/WindWidget.h"
#include "../Field/Field.h"
#include <Widgets/Image/ImageWidget.h> 
#include <Library/WidgetHandler.h>

WormLevel::WormLevel() 
	: MyWindWidget(nullptr)
	, MyField(nullptr)
{
}

void WormLevel::BeginPlay()
{
	ATurnManager = std::make_unique<TurnManager>();

	MyWindWidget = WidgetHandler::CreateWidget<WindWidget>(nullptr);
	MyWindWidget->Init();
	MyWindWidget->AddToViewport();
	
	SpawnField();
	SpawnPlayers();

	ATurnManager->NextTurn();
}

void WormLevel::SpawnField()
{
	float Ratio = 0.25f;
	float Height = Config::WindowHeight * Ratio;  // 25% of the screen
	float SpawnPositionY = Config::WindowHeight * (1 - Ratio ) + Height / 2; // 75% of the screen
	
	const FVector2D SpawnLocation = FVector2D(Config::WindowWidth / 2, SpawnPositionY);

	MyField = SpawnActor<Field>(FTransform(SpawnLocation, FVector2D(Config::WindowWidth, Height )));
	MyField->GenerateField();
}

void WormLevel::SpawnPlayers()
{
	for (int i = 0; i < Config::MaxPlayers; ++i)
	{
		CreatePlayer(MyField->GetSpawnPoint(),i);
	}
}

void WormLevel::CreatePlayer(FTransform& SpawnLocation, int PlayerId)
{
	WormsPlayer* PlayerPtr = SpawnActor<WormsPlayer>(SpawnLocation);
	
	if ( PlayerPtr )
	{
		PlayerPtr->PlayerId = PlayerId;
		PlayerPtr->Init();

		ATurnManager->RegisterObserver(PlayerPtr);
	}
}