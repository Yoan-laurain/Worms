#include "PolygonObject.h"
#include "Objects/Components/SShapeComponent.h"
#include <Library/Collision.h>

SPolygonObject::SPolygonObject() : 
	PolygonComponent(CreateComponent<SPolygonComponent>("VisualComponent")),
	Vertices(),
	bUpdateVerticesRequired(true)
{
	PolygonComponent->ObjectColor = FColor(152, 251, 152, 255);
}

SPolygonObject::~SPolygonObject() = default;

std::vector<FVector2D> SPolygonObject::GetVertices()
{
	if (bUpdateVerticesRequired)
	{
		for (int i = 0; i < PolygonComponent->Points.size(); i++)
		{
			if (Vertices.size() <= i)
			{
				Vertices.push_back(FVector2D::Zero());
			}

			FTransform transform = GetTransform();

			FVector2D finalPos = FVector2D(
				transform.Location.X + transform.Cos * PolygonComponent->Points[i].X - transform.Sin * PolygonComponent->Points[i].Y,
				transform.Location.Y + transform.Cos * PolygonComponent->Points[i].Y + transform.Sin * PolygonComponent->Points[i].X
			);

			Vertices[i] = finalPos;

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

float SPolygonObject::CalculateRotationInertia()
{
	if (bIsStatic)
	{
		return 0.f;
	}

	float widthSquared = GetSize().X * GetSize().X;
	float heightSquared = GetSize().Y * GetSize().Y;

	return (1.f / 12.f) * GetMass() * ( widthSquared + heightSquared );
}