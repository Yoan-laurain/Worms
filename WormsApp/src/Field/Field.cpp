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

    // Points de contr�le pour la courbe de B�zier
    FVector2D controlPoint1(10.0f, Config::WindowHeight / 2.0f);
    FVector2D controlPoint2(Config::WindowWidth - 10.f, Config::WindowHeight / 2.0f);

    float baseFrequency = 30.0f; 

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> frequencyDistribution(.0f, .0f);  

    baseFrequency += frequencyDistribution(gen);

    int index = 0;

    for (int i = 0; i <= numberOfCurvePoints; ++i)
    {
        float t = (i * 1.f) / (numberOfCurvePoints * 1.f);

        float x = pow(1 - t, 3) * controlPoint1.X + 3 * pow(1 - t, 2) * t * controlPoint1.X + 3 * (1 - t) * pow(t, 2) * controlPoint2.X + pow(t, 3) * controlPoint2.X;
        float y = pow(1 - t, 3) * controlPoint1.Y + 3 * pow(1 - t, 2) * t * controlPoint1.Y + 3 * (1 - t) * pow(t, 2) * controlPoint2.Y + pow(t, 3) * controlPoint2.Y;

        y += Config::WindowHeight * 0.1f * std::sin(baseFrequency * x / Config::WindowWidth);  // Sine wave with random frequency variation

        // add point relative to the center aka the get location of the field
        FVector2D point(x, y);
        FVector2D dt = point - GetLocation();

        GetPolygonComponent()->Points.push_back( dt );
    }

    // Add symetric points to close convex
    for (int i = 0; i <= numberOfCurvePoints; ++i)
    {
        FVector2D point = FVector2D(GetPolygonComponent()->Points[numberOfCurvePoints - i].X, -10.f);

        GetPolygonComponent()->Points.push_back(point);
    }

    for (int i = 0; i < Config::MaxPlayers; ++i)
    {
        AddSpawnPoint(GetTransformAt(i / (Config::MaxPlayers * 1.f)));
    }

}

FTransform Field::GetTransformAt(const float percent)
{
    //FVector2D position = pFieldPoint->GetTransform().Location;

    //FVector2D tangent = position.GetTangent();
    //float angle = std::atan2(tangent.Y, tangent.X);

    //angle = angle * 180 / MathLibrary::Pi();

    FTransform transform;
    //transform.Location = position;
    //transform.Rotation = angle;

    return transform;
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