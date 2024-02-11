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

        if (i != 0 && i < numberOfCurvePoints - 1)
        {
            FTransform spawnPoint = FTransform(point, FVector2D(0.f, 0.f), 0.f);
            AddSpawnPoint(spawnPoint);
        }
    }

    // Add symetric points to close convex
    for (int i = 0; i <= numberOfCurvePoints; ++i)
    {
        float dtY = Config::WindowHeight - GetLocation().Y;
        FVector2D point = FVector2D(GetPolygonComponent()->Points[numberOfCurvePoints - i].X, dtY - 10.f);

        GetPolygonComponent()->Points.push_back(point);
    }
}

FTransform& Field::GetSpawnPoint()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, m_SpawnPoints.size() - 1);
	int index = dist6(rng);
	FTransform spawnPoint = m_SpawnPoints[index];

    m_SpawnPoints.erase(m_SpawnPoints.begin() + index);

    return spawnPoint;
}

void Field::AddSpawnPoint(const FTransform& spawnPoint)
{
    m_SpawnPoints.push_back(spawnPoint);
}