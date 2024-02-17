#include "RectangleObject.h"
#include "Objects/Components/SShapeComponent.h"

void SRectangleObject::SetTransform(const FTransform& Transform)
{
	SActor::SetTransform(Transform);
	
	PolygonComponent->Points.clear();

	const float X = Transform.Size.X;
	const float Y = Transform.Size.Y;

	PolygonComponent->Points.emplace_back(-X, -Y);
	PolygonComponent->Points.emplace_back(-X, Y);
	PolygonComponent->Points.emplace_back(X, Y);
	PolygonComponent->Points.emplace_back(X, -Y);
}