#include "Field.h"
#include "../Config.h"
#include "../Levels/WormLevel.h"
#include "Objects/Components/SShapeComponent.h"
#include <random>
#include <cmath>
#include <Library/TVector.h>
#include <Library/MathLibrary.h>

Field::Field() : SPolygonObject()
{
    bIsStatic = true;
    GetPolygonComponent()->ObjectColor  = FColor(74 , 82 , 160);
}

void Field::GenerateFieldCurve()
{
    GetPolygonComponent()->Points.clear();

    int numberOfCurvePoints = Config::NumberOfCurvesPoints;

    for (int i = 0; i <= numberOfCurvePoints; ++i)
    {
        float x = 10.f + i * ((Config::WindowWidth-20.f) / numberOfCurvePoints);
        float y = Config::WindowHeight /2.f;

        FVector2D point(x, y);
        FVector2D dt = point - GetLocation();

        GetPolygonComponent()->Points.push_back( dt );
    }

    // Add symetric points to close convex
    for (int i = 0; i <= numberOfCurvePoints; ++i)
    {
        float dtY = Config::WindowHeight - GetLocation().Y;
        FVector2D point = FVector2D(GetPolygonComponent()->Points[numberOfCurvePoints - i].X, dtY - 10.f);

        GetPolygonComponent()->Points.push_back(point);
    }

    for (int i = 0; i < Config::MaxPlayers; ++i)
    {
        FTransform transform;
        transform.Location = GetLocation() +  GetPolygonComponent()->Points[i];
        transform.Rotation = 0.f;

        AddSpawnPoint(transform);
    }

}

FTransform& Field::GetSpawnPoint()
{
    FTransform& spawnPoint = m_SpawnPoints.back();
    m_SpawnPoints.pop_back();
    return spawnPoint;
}

void Field::AddSpawnPoint(const FTransform& spawnPoint)
{
    m_SpawnPoints.push_back(spawnPoint);
}