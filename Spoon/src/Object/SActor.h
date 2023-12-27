#pragma once

#include "Spoon/Core/SObject.h"
#include "Spoon/Library/TColor.h"

enum FActorType
{
	ActorType_None = BIT(0),
	ActorType_Circle = BIT(1),
	ActorType_Rectangle = BIT(2),
	ActorType_Convex = BIT(3)
};

struct Shape
{
	Shape() : Type(FActorType::ActorType_None), ObjectColor(FColor::White()) {};
	FActorType Type;
	FColor ObjectColor;

	FColor GetColor() const { return ObjectColor; };

	void SetColor(const FColor& color);
};

struct Circle : public Shape
{
	Circle() : radius(0) {};
	float radius;
};

struct Rectangle : public Shape
{
	Rectangle() : width(0), height(0) {};
	float width;
	float height;
};

struct Convex : public Shape
{
	Convex() : Points() {};

	std::unordered_map<int, FVector2D> Points;
};

class SPOON_API SActor : public SObject
{
	friend class Level;

public:

	SActor();

	~SActor() override;

	void DestroyActor();

	void OnEvent(class SpoonEvent& event);

#pragma region Render

public:
	Shape* MyShape;

#pragma endregion

#pragma region World

	inline class Level* GetWorld() const { return WorldRef; };

protected:

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime);

private:

	void SetWorldRef(class Level* parentRef);

private:

	FColor ObjectColor;

	class Level* WorldRef;

#pragma endregion World

};