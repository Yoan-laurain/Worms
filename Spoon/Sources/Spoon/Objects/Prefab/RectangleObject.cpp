#include "RectangleObject.h"
#include "Objects/Components/SShapeComponent.h"
#include "snpch.h"
#include "Events/MouseEvent.h"
#include <Library/Collision.h>

SRectangleObject::SRectangleObject() : SActor(),
	RectangleComponent(CreateComponent<SRectangleComponent>("VisualComponent")),
	vertices()
{
	RectangleComponent->ObjectColor = FColor( 152, 251, 152, 255);
	RectangleComponent->width = 50.f;
	RectangleComponent->height = 50.f;
		
	//bIsStatic = true;

	vertices.push_back(FVector2D(0.f,0.f));
	vertices.push_back(FVector2D(0.f,0.f));
	vertices.push_back(FVector2D(0.f,0.f));
	vertices.push_back(FVector2D(0.f,0.f));
}

SRectangleObject::~SRectangleObject()
{
}

std::vector<FVector2D> SRectangleObject::GetVertices()
{
	FVector2D dt = GetSize() * RectangleComponent->Origin;
	for (int i = 0; i < vertices.size(); i++)
	{
		if (i == 0)
		{
			vertices[i] = FVector2D(GetLocation().X - GetSize().X / 2, GetLocation().Y - GetSize().Y / 2);
		}
		else if (i == 1)
		{
			vertices[i] = FVector2D(GetLocation().X + GetSize().X / 2, GetLocation().Y - GetSize().Y / 2);
		}
		else if (i == 2)
		{
			vertices[i] = FVector2D(GetLocation().X + GetSize().X / 2, GetLocation().Y + GetSize().Y / 2);
		}
		else if (i == 3)
		{
			vertices[i] = FVector2D(GetLocation().X - GetSize().X / 2, GetLocation().Y + GetSize().Y / 2);
		}
		vertices[i] += dt;
	}

	return vertices;
}

bool SRectangleObject::IsInBound(const FVector2D& _loc)
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