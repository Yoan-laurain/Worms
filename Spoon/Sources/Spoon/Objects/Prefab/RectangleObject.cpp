#include "RectangleObject.h"
#include "Objects/Components/SShapeComponent.h"

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