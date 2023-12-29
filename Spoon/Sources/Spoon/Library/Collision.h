#pragma once

#include "Library/TVector.h"
#include "Objects/Components/SCollisionComponent.h"
#include "Objects/SActor.h"

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
inline bool Collision::CheckCollisionImpl<CircleShape, PolygonShape>(CircleShape* first, struct PolygonShape* other)
{
	FVector2D normal;
	float depth;
	return Collision::IntersectCirclePolygon(first->GetOwner()->GetLocation(), first->Radius, first->GetOwner()->GetLocation(), other->Vertices, normal, depth);
}

template <>
inline bool Collision::CheckCollisionImpl<CircleShape>(CircleShape* first, CircleShape* other)
{
	if (first == nullptr || other == nullptr)
	{
		return false;
	}
	FVector2D normal;
	float depth;
	return Collision::IntersectCircles(first->GetOwner()->GetLocation(), first->Radius, first->GetOwner()->GetLocation(), other->Radius, normal, depth);
}

template <>
inline bool Collision::CheckCollisionImpl<PolygonShape>(PolygonShape* first, PolygonShape* other)
{
	FVector2D normal;
	float depth;
	return Collision::IntersectPolygons(first->Vertices, other->Vertices, normal, depth);
}
