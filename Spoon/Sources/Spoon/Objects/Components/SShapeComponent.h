#pragma once
#include "SComponent.h"
#include "Library/TStruct.h"

enum SPOON_API FActorType
{
	ActorType_None,
	ActorType_Circle,
	ActorType_Rectangle,
	ActorType_Convex,
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

class SPOON_API SRectangleComponent : public SShapeComponent
{
	GENERATE()
public:
	SRectangleComponent(class SActor* _owner) : SShapeComponent(_owner), width(0), height(0) { Type = ActorType_Rectangle; };
	float width;
	float height;
};

class SPOON_API SConvexComponent : public SShapeComponent
{
	GENERATE()
public:
	SConvexComponent(class SActor* _owner) : SShapeComponent(_owner), Points() { Type = ActorType_Convex; };

	std::vector<FVector2D> Points;
};

class SPOON_API SSpriteComponent : public SShapeComponent
{
	GENERATE()
public:
	SSpriteComponent(class SActor* _owner) : SShapeComponent(_owner), texturePath("") { Type = ActorType_Sprite; };

	std::string texturePath;
	std::string name;
};

