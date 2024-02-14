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
    std::random_device Rd;
    std::mt19937 Gen(Rd());
        
    float Size = GetSize().X;
    std::uniform_real_distribution Dist((-Size / 2.f) * 0.75f, (Size / 2.f) * 0.75f);
    
    for ( int i = 0; i < 5; i++ )
    {
        SpawnPoints.emplace_back( FTransform( FVector2D( GetSize().X / 2.f + Dist(Gen),
            GetLocation().Y - GetSize().Y / 2.f - Config::PlayerSize / 2.f ),
            FVector2D( Config::PlayerSize ),
            0.f ) );
    }
}

FTransform& Field::GetSpawnPoint()
{
	FTransform SpawnPoint = SpawnPoints[ SpawnPoints.size() - 1 ];

    SpawnPoints.erase(SpawnPoints.begin() + SpawnPoints.size() - 1);

    return SpawnPoint;
}