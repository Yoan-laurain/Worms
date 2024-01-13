#pragma once
#include "SComponent.h"
#include "Library/TColor.h"
#include "Library/TStruct.h"

enum SPOON_API FActorType
{
	ActorType_None,
	ActorType_Circle,
	ActorType_Polygon,
	ActorType_Sprite
};

class SPOON_API SShapeComponent : public SComponent
{
	GENERATE()
public:
	SShapeComponent(class SActor* _owner) : SComponent(_owner), Type(FActorType::ActorType_None), ObjectColor(FColor::White()), Origin(0.5f) {};

	FActorType GetType() const { return Type; }

	FColor ObjectColor;
	FVector2D Origin;

protected:

	FActorType Type;
};


class SPOON_API SCircleComponent : public SShapeComponent
{
	GENERATE()
public:
	SCircleComponent(class SActor* _owner) : SShapeComponent(_owner), Radius(0) { Type = ActorType_Circle; };
	float Radius;
};

class SPOON_API SPolygonComponent : public SShapeComponent
{
	GENERATE()
public:
	SPolygonComponent(class SActor* _owner) : SShapeComponent(_owner), Points(), texturePath(""), name("") { Type = ActorType_Polygon; };

	std::vector<FVector2D> Points;
	std::string texturePath;
	std::string name;
};