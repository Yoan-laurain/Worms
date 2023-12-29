#include "Field.h"
#include "../Config.h"
#include "../Levels/WormLevel.h"
#include "Objects/Components/SShapeComponent.h"
#include <random>
#include <cmath>

Field::Field() : 
		m_FieldPoint()
{
    CurrentShape = CreateComponent<SConvexComponent>("ShapeComponent");
    CurrentShape->ObjectColor = FColor(139, 69, 19);

}

void Field::GenerateFieldCurve()
{
    CurrentShape->Points.clear();

    m_FieldPoint.clear();

    int numberOfCurvePoints = Config::NumberOfCurvesPoints;

    // Points de contr�le pour la courbe de B�zier
    FVector2D controlPoint1(0.0f, Config::WindowHeight / 2.0f);
    FVector2D controlPoint2(Config::WindowWidth, Config::WindowHeight / 2.0f);

    float baseFrequency = 10.0f; 

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> frequencyDistribution(-15.0f, 15.0f);  

    baseFrequency += frequencyDistribution(gen);

    for (int i = 0; i <= numberOfCurvePoints; ++i)
    {
        float t = (i * 1.f) / (numberOfCurvePoints * 1.f);

        float x = (1.0f - t) * (1.0f - t) * controlPoint1.X + 2.0f * (1.0f - t) * t * controlPoint1.X + t * t * controlPoint2.X;
        float y = (1.0f - t) * (1.0f - t) * controlPoint1.Y + 2.0f * (1.0f - t) * t * controlPoint1.Y + t * t * controlPoint2.Y;

        y += Config::WindowHeight * 0.1f * std::sin(baseFrequency * x / Config::WindowWidth);  // Sine wave with random frequency variation

        //FieldPoint* pFieldPoint = GetWorld()->SpawnActor<FieldPoint>(FTransform(FVector2D(x, y), FVector2D(1, 1)));

        //m_FieldPoint.push_back(std::make_unique<FieldPoint>());

        CurrentShape->Points.emplace(i, FVector2D(x, y));
        CurrentShape->Points.emplace(numberOfCurvePoints * 2 - i, FVector2D(x, Config::WindowHeight));
    }
}

FieldPoint::FieldPoint()
{
    ShapeComponent = CreateComponent<SShapeComponent>("Component");
}

void FieldPoint::OnCollide(SActor* pActor)
{
}