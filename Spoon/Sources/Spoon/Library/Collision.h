#pragma once

#include "Library/TVector.h"
#include "Objects/SActor.h"
#include "Objects/Prefab/CircleObject.h"
#include "Objects/Prefab/PolygonObject.h"
#include "Manifold.h"

class Collision
{
public:

	template <typename FirstShapeType, typename OtherShapeType = FirstShapeType>
	static bool CheckCollisionImpl(FirstShapeType* First, OtherShapeType* Other, Manifold& Collision)
	{
		return false;
	}

	template <typename FirstShapeType, typename OtherShapeType = FirstShapeType>
	static void FindContactPointImpl(FirstShapeType* First, OtherShapeType* Other, FVector2D& Cp1, FVector2D& Cp2, int& ContactCount)
	{
		return;
	}
	
    static bool IntersectCirclePolygon(const FVector2D& CircleCenter, float CircleRadius, const FVector2D& PolygonCenter,
        const std::vector<FVector2D>& Vertices, FVector2D& Normal, float& Depth);

    static bool IntersectCircles(const FVector2D& CenterA, float RadiusA,
        const FVector2D& CenterB, float RadiusB,
        FVector2D& Normal, float& Depth);

	static void ApplyCollision(SActor& First, SActor& Other, const FVector2D& Normal, float Depth);
	
    static bool IntersectPolygons(const std::vector<FVector2D>& VerticesA, const FVector2D& PolygonCenterA, const std::vector<FVector2D>& VerticesB,
		const FVector2D& PolygonCenterB,FVector2D& Normal, float& Depth);

	static bool IntersectAABBs(AlignAxisBoundingBox& A, AlignAxisBoundingBox& B);
	static void FindCirclePolygonContactPoint(const FVector2D& CircleCenter, float CircleRadius, const FVector2D& PolygonCenter, const std::vector<FVector2D>& PolygonVertices, FVector2D& Cp);
	static void PointSegmentDistance(const FVector2D& P, const FVector2D& A, const FVector2D& B, float& DistanceSquared, FVector2D& Cp);
	static void FindPolygonsContactPoints(const std::vector<FVector2D>& VerticesA, const std::vector<FVector2D>& VerticesB, FVector2D& Contact1, FVector2D& Contact2, int& ContactCount);

	static void SetCollisionManifold(SActor* First, SActor* Other, Manifold& Collision, FVector2D& Normal,
	                          float& Depth,FVector2D& Contact1, FVector2D& Contact2, int ContactCount);

private:
    static void ProjectVertices(const std::vector<FVector2D>& Vertices, const FVector2D& Axis, float& Min, float& Max);

    static void ProjectCircle(const FVector2D& Center, float Radius, const FVector2D& Axis, float& Min, float& Max);

    static size_t FindClosestPointOnPolygon(const FVector2D& CircleCenter, const std::vector<FVector2D>& Vertices);
	static void FindCirclesContactPoint(const FVector2D& CenterA, float RadiusA, const FVector2D& CenterB, FVector2D& Cp);
};

template <>
inline bool Collision::CheckCollisionImpl<SPolygonObject, SCircleObject>(SPolygonObject* First, SCircleObject* Other, Manifold& Collision)
{
	if (First == nullptr || Other == nullptr || First->GetVertices().empty())
	{
		return false;
	}

	FVector2D Normal;
	float Depth;
	
	const bool Result = IntersectCirclePolygon(Other->GetLocation(),
		Other->GetRadius(),
		First->GetLocation(),
		First->GetVertices()
		,Normal
		,Depth);

	if (Result)
	{
		ApplyCollision(*Other, *First, Normal, Depth);

		SetCollisionManifold(First, Other, Collision, Normal, Depth, Collision.Contact1, Collision.Contact2, 1);

		FindCirclePolygonContactPoint(
			Other->GetLocation()
			, Other->GetRadius()
			, First->GetLocation()
			, First->GetVertices()
			, Collision.Contact1);
	}

	return Result;
}

template <>
inline bool Collision::CheckCollisionImpl<SCircleObject, SPolygonObject>(SCircleObject* First, SPolygonObject* Other, Manifold& Collision)
{
	return CheckCollisionImpl(Other, First, Collision);
}

template <>
inline bool Collision::CheckCollisionImpl<SCircleObject>(SCircleObject* First, SCircleObject* Other, Manifold& Collision)
{
	if (First == nullptr || Other == nullptr)
	{
		return false;
	}

	FVector2D Normal;
	float Depth;
	
	const bool Result = IntersectCircles(
		First->GetLocation(),
		First->GetRadius(),
		Other->GetLocation(),
		Other->GetRadius(),
		Normal,
		Depth);
	
	if (Result)
	{
		ApplyCollision(*First, *Other, Normal, Depth);

		SetCollisionManifold(First, Other, Collision, Normal, Depth, Collision.Contact1, Collision.Contact2, 1);

		FindCirclesContactPoint(First->GetLocation(), First->GetRadius(), Other->GetLocation(), Collision.Contact1);
	}

	return Result;
}

template <>
inline bool Collision::CheckCollisionImpl<SPolygonObject>(SPolygonObject* First, SPolygonObject* Other, Manifold& Collision)
{
	if (First == nullptr || Other == nullptr || Other->GetVertices().empty() || First->GetVertices().empty())
	{
		return false;
	}

	FVector2D Normal;
	float Depth;
	
	const bool Result = IntersectPolygons(
		First->GetVertices(),
		First->GetLocation(),
		Other->GetVertices(),
		Other->GetLocation(),
		Normal,
		Depth);

	if (Result)
	{
		ApplyCollision(*First, *Other, Normal, Depth);

		SetCollisionManifold( First, Other, Collision, Normal, Depth, Collision.Contact1, Collision.Contact2, 0);
		
		FindPolygonsContactPoints(
			First->GetVertices(),
			Other->GetVertices(),
			Collision.Contact1,
			Collision.Contact2,
			Collision.ContactCount);
	}

	return Result;
}