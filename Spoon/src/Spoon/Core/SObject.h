#pragma once
#include "Core.h"
#include <snpch.h>
#include "Spoon/Library/TStruct.h"

class ObjectRender;
class CollisionShape;

// Object base. 
class SPOON_API SObject
{
public:
	
	SObject();

	virtual ~SObject();

protected:

	FTransform ObjectTransform;

public:

	bool bIsStatic;

	std::unique_ptr<CollisionShape> collisionShape;

	FVector2D GetLocation() const;

	void SetLocation(const FVector2D& loc);

	FVector2D GetSize() const;

	void SetSize(const FVector2D& size);

	FTransform GetTransform() const;

	void SetTransform(const FTransform& transform);

	bool IsInBound(const FVector2D& _loc);

	bool CheckCollision(const SObject& other) const;

	void OnCollide(const SObject& other);
};

