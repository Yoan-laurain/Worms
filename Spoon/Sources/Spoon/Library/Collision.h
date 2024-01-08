#pragma once

#include "Library/TVector.h"
#include "Objects/Components/SCollisionComponent.h"
#include "Objects/SActor.h"
#include "Objects/Prefab/CircleObject.h"
#include "Objects/Prefab/PolygonObject.h"

class Collision
{
public:

	template <typename FirstShapeType, typename OtherShapeType = FirstShapeType>
	static bool CheckCollisionImpl(FirstShapeType* first, OtherShapeType* other)
	{
		return false;
	};

    static bool IntersectCirclePolygon(const FVector2D& circleCenter, float circleRadius, const FVector2D& polygonCenter,
        const std::vector<FVector2D>& vertices, FVector2D& normal, float& depth);

    static bool IntersectCircles(const FVector2D& centerA, float radiusA,
        const FVector2D& centerB, float radiusB,
        FVector2D& normal, float& depth);

	static void ApplyCollision(SActor* first, SActor* other, const FVector2D& normal, float depth);
public:
    static bool IntersectPolygons(const std::vector<FVector2D>& verticesA, const std::vector<FVector2D>& verticesB,
        FVector2D& normal, float& depth);

private:
    static void ProjectVertices(const std::vector<FVector2D>& vertices, const FVector2D& axis, float& min, float& max);

    static void ProjectCircle(const FVector2D& center, float radius, const FVector2D& axis, float& min, float& max);

    static size_t FindClosestPointOnPolygon(const FVector2D& circleCenter, const std::vector<FVector2D>& vertices);

    static FVector2D FindArithmeticMean(const std::vector<FVector2D>& vertices);
};

template <>
inline bool Collision::CheckCollisionImpl<SPolygonObject, SCircleObject>(SPolygonObject* first, SCircleObject* other)
{
	if (first == nullptr || other == nullptr || first->GetVertices().size() == 0)
	{
		return false;
	}

	FVector2D normal;
	float depth;
	const bool Result = Collision::IntersectCirclePolygon(other->GetLocation(), other->GetRadius(), first->GetLocation(), first->GetVertices(), normal, depth);

	if (Result)
	{
		ApplyCollision(other, first, normal, depth);
	}
	else
	{ }

	return Result;
}

template <>
inline bool Collision::CheckCollisionImpl<SCircleObject, SPolygonObject>(SCircleObject* first, SPolygonObject* other)
{
	if (first == nullptr || other == nullptr || other->GetVertices().size() == 0)
	{
		return false;
	}

	FVector2D normal;
	float depth;
	const bool Result = Collision::IntersectCirclePolygon(first->GetLocation(), first->GetRadius(), other->GetLocation(), other->GetVertices(), normal, depth);

	if (Result)
	{
		ApplyCollision(first, other, normal, depth);
	}

	return Result;
}

template <>
inline bool Collision::CheckCollisionImpl<SCircleObject>(SCircleObject* first, SCircleObject* other)
{
	if (first == nullptr || other == nullptr)
	{
		return false;
	}

	FVector2D normal;
	float depth;
	const bool Result = Collision::IntersectCircles(first->GetLocation(), first->GetRadius(), other->GetLocation(), other->GetRadius(), normal, depth);
	
	if (Result)
	{
		ApplyCollision(first, other, normal, depth);
	}

	return Result;
}

template <>
inline bool Collision::CheckCollisionImpl<SPolygonObject>(SPolygonObject* first, SPolygonObject* other)
{
	if (first == nullptr || other == nullptr || other->GetVertices().size() == 0 || first->GetVertices().size() == 0)
	{
		return false;
	}

	FVector2D normal;
	float depth;
	const bool Result = Collision::IntersectPolygons(first->GetVertices(), other->GetVertices(), normal, depth);

	if (Result)
	{
		ApplyCollision(first, other, normal, depth);
	}

	return Result;
}