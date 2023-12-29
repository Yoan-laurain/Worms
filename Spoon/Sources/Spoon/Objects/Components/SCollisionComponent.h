#pragma once
#include "SComponent.h"
#include "Library/TVector.h"

class SPOON_API BaseShape : public SComponent
{
public:
    BaseShape(class SActor* _owner, const FVector2D& _center);
    FVector2D Center;
};

struct SPOON_API CircleShape : public BaseShape
{
	CircleShape(class SActor*_owner, const FVector2D& _center, float _radius) : BaseShape(_owner, _center), Radius(_radius) {}

	float Radius;
};

struct SPOON_API PolygonShape : public BaseShape
{
	PolygonShape(class SActor* _owner, const FVector2D& _center, const std::vector<FVector2D> _vertices) : BaseShape(_owner, _center), Vertices(_vertices) {}

	std::vector<FVector2D> Vertices;
};
