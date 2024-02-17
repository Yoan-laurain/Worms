#pragma once

#include "SComponent.h"
#include "Library/TVector.h"

class SActor;

class SPOON_API BaseShape : public SComponent
{
public:
    BaseShape( SActor* _owner) : SComponent(_owner) {}

};

class SPOON_API CircleShape : public BaseShape
{
public:
	CircleShape( SActor*_owner) : BaseShape(_owner), Radius(0) {}

	float Radius;
};

class SPOON_API PolygonShape : public BaseShape
{
public:
	PolygonShape( SActor* _owner) : BaseShape(_owner) {}

	std::vector<FVector2D> Vertices;
};
