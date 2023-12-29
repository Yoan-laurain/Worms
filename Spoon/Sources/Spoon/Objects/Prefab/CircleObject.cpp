#include "CircleObject.h"
#include "Objects/Components/SShapeComponent.h"
#include "snpch.h"
#include "Events/MouseEvent.h"


SCircleObject::SCircleObject() : CircleComponent(CreateComponent<SCircleComponent>("VisualComponent"))
{
	CircleComponent->Radius = 50.0f;
	CircleComponent->ObjectColor = FColor::White();
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

bool SCircleObject::IsInBound(const FVector2D& _loc) const
{
	FVector2D vecDirection = GetLocation() - _loc;
	float distance = vecDirection.GetLength();
	return distance <= GetRadius();
}

bool SCircleObject::OnMouseEvent(MouseMovedEvent& _event)
{
	bIsHovered = IsInBound(_event.GetLoc());

	mouseLoc = (bIsPressed) ? _event.GetLoc() : GetLocation();

	return false;
}
