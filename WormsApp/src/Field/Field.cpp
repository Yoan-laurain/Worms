#include "Field.h"
#include "../Config.h"
#include "../Levels/WormLevel.h"
#include "Objects/Components/SShapeComponent.h"
#include <random>
#include <cmath>
#include <Library/TVector.h>
#include <Library/MathLibrary.h>


Field::Field() : 
		m_FieldPoint()
{
    ShapeComponent = CreateComponent<SConvexComponent>("ShapeComponent");
    ShapeComponent->ObjectColor = FColor(139, 69, 19);
}

void Field::GenerateFieldCurve()
{
    SConvexComponent* pConvex = static_cast<SConvexComponent*>(ShapeComponent);
    pConvex->Points.clear();

    m_FieldPoint.clear();

    int numberOfCurvePoints = Config::NumberOfCurvesPoints;

    // Points de contr�le pour la courbe de B�zier
    FVector2D controlPoint1(10.0f, Config::WindowHeight / 2.0f);
    FVector2D controlPoint2(Config::WindowWidth-10, Config::WindowHeight / 2.0f);

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

        //y += Config::WindowHeight * 0.1f * std::sin(baseFrequency * x / Config::WindowWidth);  // Sine wave with random frequency variation

        FieldPoint* pFieldPoint = GetWorld()->SpawnActor<FieldPoint>(FTransform(FVector2D(x, y-10), FVector2D(1, 1)));
        m_FieldPoint.push_back(pFieldPoint);

        CurrentShape->Points.push_back(FVector2D(x, y-10));
    }

    // Add symetric points to close convex
    for (int i = 0; i <= numberOfCurvePoints; ++i)
    {
        CurrentShape->Points.push_back(FVector2D(CurrentShape->Points[numberOfCurvePoints - i].X, Config::WindowHeight-10));
    }

    AddSpawnPoint(GetTransformAt(0.25f));
    AddSpawnPoint(GetTransformAt(0.75f));
}

FTransform Field::GetTransformAt(float percent)
{
    if (m_FieldPoint.size() == 0)
    {
        return FTransform();
    }

    int index = percent * (m_FieldPoint.size() - 1);
    FieldPoint* pFieldPoint = m_FieldPoint[index];

    FVector2D position = pFieldPoint->GetTransform().Location;

    FVector2D tangent = position.GetTangent();
    float angle = std::atan2(tangent.Y, tangent.X);

    angle = angle * 180 / MathLibrary::Pi();

    FTransform transform;
    transform.Location = position;
    transform.Rotation = angle;

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

FieldPoint::FieldPoint()
{
    ShapeComponent = CreateComponent<SCircleComponent>("CircleComponent");  
    ShapeComponent->ObjectColor = FColor(255, 255, 255);
    ShapeComponent->Radius = 5.0f;

}

void FieldPoint::OnCollide(SActor* pActor)
{
}