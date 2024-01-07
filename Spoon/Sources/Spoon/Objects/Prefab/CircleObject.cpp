#include "CircleObject.h"
#include "Objects/Components/SShapeComponent.h"
#include "snpch.h"
#include "Events/MouseEvent.h"
#include <Library/Collision.h>

SCircleObject::SCircleObject() : CircleComponent(CreateComponent<SCircleComponent>("VisualComponent"))
{
	CircleComponent->Radius = 25.f;
	CircleComponent->ObjectColor = FColor(80, 40, 200);
}

SCircleObject::~SCircleObject()
{
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

bool SCircleObject::IsInBound(const FVector2D& _loc)
{
	FVector2D normal;
	float depth;

	return Collision::IntersectCircles(GetLocation(), CircleComponent->Radius, _loc, 5.f, normal, depth);
}