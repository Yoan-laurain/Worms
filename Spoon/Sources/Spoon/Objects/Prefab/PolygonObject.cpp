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

std::vector<FVector2D>& SPolygonObject::GetVertices()
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

bool SPolygonObject::IsInBound(const FVector2D& Loc)
{
	if (GetVertices().empty())
	{
		return false;
	}

	FVector2D Normal;
	float Depth;
	const bool Result = Collision::IntersectCirclePolygon(Loc, 5.0f, GetLocation(), GetVertices(), Normal, Depth);

	return Result;
}

void SPolygonObject::Move(const FVector2D& Loc)
{
	SActor::Move(Loc);
	bUpdateVerticesRequired = true;
}

void SPolygonObject::AddForce(const FVector2D& Force)
{
	SActor::AddForce(Force);
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