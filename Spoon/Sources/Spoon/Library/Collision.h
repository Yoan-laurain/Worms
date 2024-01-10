#pragma once

#include "Library/TVector.h"
#include "Objects/Components/SCollisionComponent.h"
#include "Objects/SActor.h"
#include "Objects/Prefab/CircleObject.h"
#include "Objects/Prefab/PolygonObject.h"
#include "Manifold.h"

class Collision
{
public:

	template <typename FirstShapeType, typename OtherShapeType = FirstShapeType>
	static bool CheckCollisionImpl(FirstShapeType* first, OtherShapeType* other, Manifold& collision)
	{
		return false;
	};

	template <typename FirstShapeType, typename OtherShapeType = FirstShapeType>
	static void FindContactPointImpl(FirstShapeType* first, OtherShapeType* other, FVector2D& cp1, FVector2D& cp2, int& contactCount)
	{
		return;
	};


    static bool IntersectCirclePolygon(const FVector2D& circleCenter, float circleRadius, const FVector2D& polygonCenter,
        const std::vector<FVector2D>& vertices, FVector2D& normal, float& depth);

    static bool IntersectCircles(const FVector2D& centerA, float radiusA,
        const FVector2D& centerB, float radiusB,
        FVector2D& normal, float& depth);

	static void ApplyCollision(SActor& first, SActor& other, const FVector2D& normal, float depth);

public:
    static bool IntersectPolygons(const std::vector<FVector2D>& verticesA, const FVector2D& polygonCenterA, const std::vector<FVector2D>& verticesB,
		const FVector2D& polygonCenterB,FVector2D& normal, float& depth);

	static bool IntersectAABBs(AlignAxisBoundingBox& a, AlignAxisBoundingBox& b);
private:
    static void ProjectVertices(const std::vector<FVector2D>& vertices, const FVector2D& axis, float& min, float& max);

    static void ProjectCircle(const FVector2D& center, float radius, const FVector2D& axis, float& min, float& max);

    static size_t FindClosestPointOnPolygon(const FVector2D& circleCenter, const std::vector<FVector2D>& vertices);
	static void FindContactPoint(const FVector2D& centerA, float radiusA, const FVector2D& centerB, FVector2D& cp);
};

template <>
inline bool Collision::CheckCollisionImpl<SPolygonObject, SCircleObject>(SPolygonObject* first, SCircleObject* other, Manifold& collision)
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
		ApplyCollision(*other, *first, normal, depth);

		collision.BodyA = first;
		collision.BodyB = other;
		collision.Normal = normal;
		collision.Depth = depth;
		collision.Contact1 = FVector2D::Zero();
		collision.Contact2 = FVector2D::Zero();
		collision.ContactCount = 0;
	}

	return Result;
}

template <>
inline bool Collision::CheckCollisionImpl<SCircleObject, SPolygonObject>(SCircleObject* first, SPolygonObject* other, Manifold& collision)
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
		ApplyCollision(*first, *other, normal, depth);

		collision.BodyA = first;
		collision.BodyB = other;
		collision.Normal = normal;
		collision.Depth = depth;
		collision.Contact1 = FVector2D::Zero();
		collision.Contact2 = FVector2D::Zero();
		collision.ContactCount = 0;
	}

	return Result;
}

template <>
inline bool Collision::CheckCollisionImpl<SCircleObject>(SCircleObject* first, SCircleObject* other, Manifold& collision)
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
		ApplyCollision(*first, *other, normal, depth);

		collision.BodyA = first;
		collision.BodyB = other;
		collision.Normal = normal;
		collision.Depth = depth;
		collision.Contact1 = FVector2D::Zero();
		collision.Contact2 = FVector2D::Zero();
		collision.ContactCount = 1;

		FindContactPoint(first->GetLocation(), first->GetRadius(), other->GetLocation(), collision.Contact1);
	}

	return Result;
}

template <>
inline bool Collision::CheckCollisionImpl<SPolygonObject>(SPolygonObject* first, SPolygonObject* other, Manifold& collision)
{
	if (first == nullptr || other == nullptr || other->GetVertices().size() == 0 || first->GetVertices().size() == 0)
	{
		return false;
	}

	FVector2D normal;
	float depth;
	const bool Result = Collision::IntersectPolygons(first->GetVertices(),first->GetLocation(), other->GetVertices(),other->GetLocation(), normal, depth);

	if (Result)
	{
		ApplyCollision(*first, *other, normal, depth);

		collision.BodyA = first;
		collision.BodyB = other;
		collision.Normal = normal;
		collision.Depth = depth;
		collision.Contact1 = FVector2D::Zero();
		collision.Contact2 = FVector2D::Zero();
		collision.ContactCount = 0;
	}

	return Result;
}
