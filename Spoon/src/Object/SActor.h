#pragma once

#include "Spoon/Core/SObject.h"
#include "Spoon/Library/TColor.h"

enum FActorType
{
	ActorType_None = BIT(0),
	ActorType_Circle = BIT(1),
	ActorType_Rectangle = BIT(2),
	ActorType_Convex = BIT(3),
	ActorType_Sprite = BIT(4),
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

struct Sprite : public Shape
{
	Sprite() : texturePath("") {};

	std::string texturePath;
	std::string name;
};

class SPOON_API SActor : public SObject
{
	friend class Level;

	// Todo : A delete when key application
	friend class Application;

public:

	SActor();

	virtual ~SActor();

	SActor(SActor&) = default;

	void DestroyActor();

	inline class Level* GetWorld() const { return WorldRef; };

protected:

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime);

	virtual bool OnMouseEvent(class MouseMovedEvent& _event);

	virtual bool OnMousePressedEvent(class MouseButtonPressedEvent& _event);

	virtual bool OnMouseRelesedEvent(class MouseButtonReleasedEvent& _event);

private:

	void OnEvent(class SpoonEvent& event);

	void SetWorldRef(class Level* parentRef);

public:

	Shape* MyShape;

protected:

	template<typename T>
	T* CreateComponent()
	{
		T* tmp = new T(this);
		ComposanList.push_back(std::unique_ptr<T>(tmp));
		return tmp;
	}

	bool bIsHovered;

	bool bIsPressed;

	FVector2D mouseLoc;

private:

	std::vector<std::unique_ptr<class SComponent>> ComposanList;

	FColor ObjectColor;

	class Level* WorldRef;

};