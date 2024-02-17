#include "CircleObject.h"
#include "Objects/Components/SShapeComponent.h"
#include "Library/Collision.h"

SCircleObject::SCircleObject() : CircleComponent(CreateComponent<SCircleComponent>("VisualComponent"))
{
	CircleComponent->ObjectColor = FColor(80, 40, 200);
}

void SCircleObject::SetRadius(const float Radius)
{
	CircleComponent->Radius = Radius;
}

float SCircleObject::GetRadius() const
{
	return CircleComponent->Radius;
}

void SCircleObject::SetColor(const FColor& Color)
{
	CircleComponent->ObjectColor = Color;
}

const FColor& SCircleObject::GetColor() const
{
	return CircleComponent->ObjectColor;
}

SCircleComponent* SCircleObject::GetCircleComponent() const
{
	return CircleComponent;
}

bool SCircleObject::IsInBound(const FVector2D& Loc)
{
	FVector2D Normal;
	float Depth;

	return Collision::IntersectCircles(GetLocation(), CircleComponent->Radius, Loc, 5.f, Normal, Depth);
}

void SCircleObject::SetTransform(const FTransform& Transform)
{
	SActor::SetTransform(Transform);
	CircleComponent->Radius = Transform.Size.X / 2.f;
}