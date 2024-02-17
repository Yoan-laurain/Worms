#include "RectangleObject.h"
#include "Objects/Components/SShapeComponent.h"

void SRectangleObject::SetTransform(const FTransform& transform)
{
	SActor::SetTransform(transform);
	
	PolygonComponent->Points.clear();

	const float X = transform.Size.X;
	const float Y = transform.Size.Y;

	PolygonComponent->Points.emplace_back(-X, -Y);
	PolygonComponent->Points.emplace_back(-X, Y);
	PolygonComponent->Points.emplace_back(X, Y);
	PolygonComponent->Points.emplace_back(X, -Y);
}