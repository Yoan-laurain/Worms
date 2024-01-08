#include "PolygonObject.h"
#include "Objects/Components/SShapeComponent.h"
#include <Library/Collision.h>

SPolygonObject::SPolygonObject() : SActor(),
	PolygonComponent(CreateComponent<SPolygonComponent>("VisualComponent")),
	Vertices()
{
	PolygonComponent->ObjectColor = FColor(152, 251, 152, 255);
}

SPolygonObject::~SPolygonObject()
{
}

std::vector<FVector2D> SPolygonObject::GetVertices()
{
	FVector2D dt = GetSize() * PolygonComponent->Origin;

	for (int i = 0; i < PolygonComponent->Points.size(); i++)
	{
		if (Vertices.size() <= i)
		{
			Vertices.push_back(FVector2D());
		}

		Vertices[i] = GetLocation() + PolygonComponent->Points[i] + dt;
	}

	return Vertices;
}

bool SPolygonObject::IsInBound(const FVector2D& _loc)
{
	if (GetVertices().size() == 0)
	{
		return false;
	}

	FVector2D normal;
	float depth;
	const bool Result = Collision::IntersectCirclePolygon(_loc, 5.0f, GetLocation(), GetVertices(), normal, depth);

	return Result;
}