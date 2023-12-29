#pragma once

#include "Spoon/Core/SObject.h"
#include "Spoon/Library/TColor.h"
#include "Spoon/Library/TStruct.h"
#include "Spoon/Library/Collision.h"
#include "Object/Component/CollisionShape.h"

enum SPOON_API FActorType
{
	ActorType_None,
	ActorType_Circle,
	ActorType_Rectangle,
	ActorType_Convex,
	ActorType_Sprite
};

class SPOON_API Shape
{
public:
	Shape() : Type(FActorType::ActorType_None), ObjectColor(FColor::White()) {};
	FActorType Type;
	FColor ObjectColor;
};

class SPOON_API Circle : public Shape
{
public:
	Circle() : radius(0) {};
	float radius;
};

class SPOON_API Rectangle : public Shape
{
public:
	Rectangle() : width(0), height(0) {};
	float width;
	float height;
};

class SPOON_API Convex : public Shape
{
public:
	Convex() : Points() {};

	std::unordered_map<int, FVector2D> Points;
};

class SPOON_API Sprite : public Shape
{
public:
	Sprite() : texturePath("") {};

	std::string texturePath;
	std::string name;
};

class SPOON_API SActor : public SObject
{
	friend class Level;

	// Todo : A delete when key application
	friend class Application;

	std::mutex _mutex;

public:

	SActor();

	virtual ~SActor();

	void DestroyActor();

	inline class Level* GetWorld() const { return WorldRef; };

	/************************************************************************/
	/* GetColor																*/
	/************************************************************************/

	FColor GetColor() const;

	void SetColor(const FColor& color);

	/************************************************************************/
	/* Transform															*/
	/************************************************************************/

	FVector2D GetLocation() const;

	void SetLocation(const FVector2D& loc);

	FVector2D GetSize() const;

	void SetSize(const FVector2D& size);

	FTransform GetTransform() const;

	void SetTransform(const FTransform& transform);

	/************************************************************************/
	/* Collision															*/
	/************************************************************************/

	bool IsInBound(const FVector2D& _loc) const;

	bool CheckCollision(SActor* other) const;

	void OnCollide(SActor* other);

	FActorType GetType() const;

	Shape* GetShape() const;

	void SetShape(Shape* _newShape);

protected:

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime);

	virtual bool OnMouseEvent(class MouseMovedEvent& _event);

	virtual bool OnMousePressedEvent(class MouseButtonPressedEvent& _event);

	virtual bool OnMouseRelesedEvent(class MouseButtonReleasedEvent& _event);

	template<typename T>
	T* CreateComponent()
	{
		T* tmp = new T(this);
		ComposanList.push_back(std::unique_ptr<T>(tmp));
		return tmp;
	}

private:

	void OnEvent(class SpoonEvent& event);

	void SetWorldRef(class Level* parentRef);

public:

	bool bIsStatic;

protected:

	bool bIsHovered;

	bool bIsPressed;

	FVector2D mouseLoc;

	FTransform ObjectTransform;

private:

	std::unique_ptr<Shape> MyShape;

	std::vector<std::unique_ptr<class SComponent>> ComposanList;

	class Level* WorldRef;

};