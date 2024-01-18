#include "RectangleObject.h"
#include "Objects/Components/SShapeComponent.h"
#include "Library/MathLibrary.h"

SRectangleObject::SRectangleObject()
{
}

void SRectangleObject::SetTransform(const FTransform& transform)
{
	SActor::SetTransform(transform);
	PolygonComponent->Points.clear();

	float X = transform.Size.X;
	float Y = transform.Size.Y;

	PolygonComponent->Points.push_back(FVector2D(-X, -Y));
	PolygonComponent->Points.push_back(FVector2D(-X, Y));
	PolygonComponent->Points.push_back(FVector2D(X, Y));
	PolygonComponent->Points.push_back(FVector2D(X, -Y));
}

void SRectangleObject::AddRotation(const float addRotation)
{
	SActor::AddRotation(addRotation);
	static const float RotationAngle = 360 / 4;
	PolygonComponent->Points.clear();
	PolygonComponent->Points.resize(4, FVector2D::Zero());
	for (unsigned int i = 0; i < 4; ++i)
	{
		float rot = RotationAngle * i + (45 + ObjectTransform.Rotation * (180.f / MathLibrary::Pi));
		rot /= (180.f/MathLibrary::Pi);
		PolygonComponent->Points[i] = FVector2D(std::cosf(rot) * GetSize().X, std::sinf(rot) * GetSize().Y);
	}

}
