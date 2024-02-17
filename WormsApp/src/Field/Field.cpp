#include "Field.h"
#include "../Levels/WormLevel.h"
#include "../Config.h"
#include <Objects/Components/SShapeComponent.h>
#include <random>
#include <Library/TVector.h>

Field::Field() 
{
    bIsStatic = true;
    GetPolygonComponent()->ObjectColor  = FColor(127, 127, 127, 255);
}

void Field::GenerateField()
{
    GetPolygonComponent()->Points.emplace_back(-GetSize().X / 2.f, -GetSize().Y / 2.f);
    GetPolygonComponent()->Points.emplace_back(GetSize().X / 2.f, -GetSize().Y / 2.f);
    GetPolygonComponent()->Points.emplace_back(GetSize().X / 2.f, GetSize().Y / 2.f);
    GetPolygonComponent()->Points.emplace_back(-GetSize().X / 2.f, GetSize().Y / 2.f);

    CreateSpawnPoints();
}

void Field::CreateSpawnPoints()
{
    float Offsets [] = { -500.f, -300.f, 0.f, 200.f, 500.f };
    
    for (const int Offset : Offsets)
    {
        SpawnPoints.emplace_back( FTransform( FVector2D( GetSize().X / 2.f + Offset,
            GetLocation().Y - GetSize().Y / 2.f - Config::PlayerSize / 2.f ),
            FVector2D( Config::PlayerSize ),
            0.f ) );
    }
}

FTransform Field::GetSpawnPoint()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, SpawnPoints.size() - 1);
    int RandomIndex = dis(gen);
    
	FTransform Spawn = SpawnPoints[RandomIndex];

    SpawnPoints.erase( SpawnPoints.begin() + RandomIndex );

    return Spawn;
}