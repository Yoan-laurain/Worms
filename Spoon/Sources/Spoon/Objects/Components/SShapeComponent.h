#pragma once

#include "SComponent.h"
#include "Library/TColor.h"

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
		SShapeComponent(SActor* Owner)
			: SComponent(Owner)
			, ObjectColor(FColor::Zero())
			, Origin(0.5f)
			, TexturePath("")
			, Type(ActorType_None)
		{
			
		}

		virtual ~SShapeComponent() override = default;

		FActorType GetType() const { return Type; }

		FColor ObjectColor;
		FVector2D Origin;
		std::string TexturePath;

	protected:

		FActorType Type;
};

class SPOON_API SCircleComponent : public SShapeComponent
{
	GENERATE()
	
	public:
		SCircleComponent(SActor* Owner)
			: SShapeComponent(Owner)
			, Radius(0)
		{
			Type = ActorType_Circle;
		}

		virtual ~SCircleComponent() override = default;
	
		float Radius;
};

class SPOON_API SPolygonComponent : public SShapeComponent
{
	GENERATE()
	
	public:
		SPolygonComponent(SActor* Owner)
			: SShapeComponent(Owner)
			, Name("")
		{
			Type = ActorType_Polygon;
		}

		virtual ~SPolygonComponent() override = default;

		std::vector<FVector2D> Points;
		std::string Name;
};