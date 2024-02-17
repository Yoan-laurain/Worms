#include "PolygonObject.h"
#include "Objects/Components/SShapeComponent.h"
#include "Library/Collision.h"

SPolygonObject::SPolygonObject() : 
	bUpdateVerticesRequired(true),
	PolygonComponent(CreateComponent<SPolygonComponent>("VisualComponent"))
{
}

SPolygonComponent* SPolygonObject::GetPolygonComponent() const
{
	return PolygonComponent;
}

std::vector<FVector2D> SPolygonObject::GetVertices()
{
	if (bUpdateVerticesRequired)
	{
		for (int i = 0; i < PolygonComponent->Points.size(); i++)
		{
			if (Vertices.size() <= i)
			{
				Vertices.emplace_back();
			}

			Vertices[i] = GetLocation() + PolygonComponent->Points[i];
		}
		bUpdateVerticesRequired = false;
	}

	return Vertices;
}

bool SPolygonObject::IsInBound(const FVector2D& _loc)
{
	if (GetVertices().empty())
	{
		return false;
	}

	FVector2D normal;
	float depth;
	const bool Result = Collision::IntersectCirclePolygon(_loc, 5.0f, GetLocation(), GetVertices(), normal, depth);

	return Result;
}

void SPolygonObject::Move(const FVector2D& loc)
{
	SActor::Move(loc);
	bUpdateVerticesRequired = true;
}

void SPolygonObject::AddForce(const FVector2D& force)
{
	SActor::AddForce(force);
	bUpdateVerticesRequired = true;
}

void SPolygonObject::Tick(float DeltaTime)
{
	SActor::Tick(DeltaTime);

	if (LinearVelocity != FVector2D::Zero())
	{
		bUpdateVerticesRequired = true;
	}
}