#pragma once
#include "SComponent.h"
#include "Library/TVector.h"

class SPOON_API BaseShape : public SComponent
{
public:
    BaseShape(class SActor* _owner) : SComponent(_owner) {};

};

class SPOON_API CircleShape : public BaseShape
{
public:
	CircleShape(class SActor*_owner) : BaseShape(_owner), Radius(0) {}

	float Radius;
};

class SPOON_API PolygonShape : public BaseShape
{
public:
	PolygonShape(class SActor* _owner) : BaseShape(_owner), Vertices() {}

	std::vector<FVector2D> Vertices;
};
