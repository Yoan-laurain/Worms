#pragma once

#include "SComponent.h"
#include "Library/TVector.h"

class SActor;

class SPOON_API BaseShape : public SComponent
{
	public:
	    BaseShape( SActor* Owner) : SComponent(Owner) {}
		virtual ~BaseShape() override = default;

};

class SPOON_API CircleShape : public BaseShape
{
	public:
		CircleShape( SActor*Owner) : BaseShape(Owner), Radius(0) {}
		virtual ~CircleShape() override = default;

		float Radius;
};

class SPOON_API PolygonShape : public BaseShape
{
	public:
		PolygonShape( SActor* Owner) : BaseShape(Owner) {}
		virtual ~PolygonShape() override = default;

		std::vector<FVector2D> Vertices;
};