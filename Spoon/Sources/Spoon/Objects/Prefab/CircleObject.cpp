#include "CircleObject.h"
#include "Objects/Components/SShapeComponent.h"
#include "Library/Collision.h"

SCircleObject::SCircleObject() : CircleComponent(CreateComponent<SCircleComponent>("VisualComponent"))
{
	CircleComponent->ObjectColor = FColor(80, 40, 200);
}

void SCircleObject::SetRadius(const float radius)
{
	CircleComponent->Radius = radius;
}

float SCircleObject::GetRadius() const
{
	return CircleComponent->Radius;
}

void SCircleObject::SetColor(const FColor& color)
{
	CircleComponent->ObjectColor = color;
}

const FColor& SCircleObject::GetColor() const
{
	return CircleComponent->ObjectColor;
}

SCircleComponent* SCircleObject::GetCircleComponent() const
{
	return CircleComponent;
}

bool SCircleObject::IsInBound(const FVector2D& _loc)
{
	FVector2D normal;
	float depth;

	return Collision::IntersectCircles(GetLocation(), CircleComponent->Radius, _loc, 5.f, normal, depth);
}

void SCircleObject::SetTransform(const FTransform& transform)
{
	SActor::SetTransform(transform);
	CircleComponent->Radius = transform.Size.X / 2.f;
}