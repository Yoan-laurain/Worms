#include "PolygonObject.h"
#include "Objects/Components/SShapeComponent.h"
#include <Library/Collision.h>

SPolygonObject::SPolygonObject() : SActor(),
	PolygonComponent(CreateComponent<SPolygonComponent>("VisualComponent")),
	Vertices(),
	bUpdateVerticesRequired(true)
{
	PolygonComponent->ObjectColor = FColor(152, 251, 152, 255);
}

SPolygonObject::~SPolygonObject()
{
}

std::vector<FVector2D> SPolygonObject::GetVertices()
{
	if (bUpdateVerticesRequired)
	{
		for (int i = 0; i < PolygonComponent->Points.size(); i++)
		{
			if (Vertices.size() <= i)
			{
				Vertices.push_back(FVector2D());
			}

			Vertices[i] = GetLocation() + PolygonComponent->Points[i];
		}
		bUpdateVerticesRequired = false;
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

float SPolygonObject::CalculateRotationInertia()
{
	float widthSquared = GetSize().X * GetSize().X;
	float heightSquared = GetSize().Y * GetSize().Y;

	return (1.f / 12.f) * Mass * ( widthSquared + heightSquared );
}