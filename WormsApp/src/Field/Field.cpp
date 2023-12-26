#include "Field.h"
#include "../Config.h"
#include "../Levels/WormLevel.h"
#include <random>
#include <cmath>

Field::Field() : 
		m_FieldPoint()
{
    SetColor( FColor(139, 69, 19) );  // Couleur brune pour le terrain
}

void Field::GenerateFieldCurve()
{
    m_FieldPoint.clear();

    int numberOfCurvePoints = Config::NumberOfCurvesPoints;

    //sf::ConvexShape terrainShape;
    //terrainShape.setPointCount(numberOfCurvePoints * 2);

    // Points de contrôle pour la courbe de Bézier
    FVector2D controlPoint1(0.0f, Config::WindowHeight / 2.0f);
    FVector2D controlPoint2(Config::WindowWidth, Config::WindowHeight / 2.0f);

    float frequency = 15.0f;  // Ajustement de la fréquence de l'onde sinusoïdale

    for (int i = 0; i <= numberOfCurvePoints; ++i)
    {
        float t = static_cast<float>(i) / static_cast<float>(numberOfCurvePoints);

        float x = (1.0f - t) * (1.0f - t) * controlPoint1.X + 2.0f * (1.0f - t) * t * controlPoint1.X + t * t * controlPoint2.X;
        float y = (1.0f - t) * (1.0f - t) * controlPoint1.Y + 2.0f * (1.0f - t) * t * controlPoint1.Y + t * t * controlPoint2.Y;

        y += Config::WindowHeight * 0.1f * std::sin(frequency * x / Config::WindowWidth);  // onde sinusoïdale à la coordonnée y

        FieldPoint* pFieldPoint = GetWorld()->SpawnActor<FieldPoint>(FTransform(FVector2D(x, y), FVector2D(1, 1)));

        m_FieldPoint.push_back(std::make_unique<FieldPoint>(x, y));

        //terrainShape.setPoint(i, sf::Vector2f(x, y));
        //terrainShape.setPoint(2 * numberOfCurvePoints - i, sf::Vector2f(x, Config::WindowHeight));
    }
}

FieldPoint::FieldPoint(float x, float y) 
{
    SetLocation(FVector2D(x, y));
}

void FieldPoint::OnCollide(SActor* pActor)
{
}