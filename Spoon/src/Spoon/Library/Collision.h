#pragma once

#include "Spoon/Library/TVector.h"

class Collision
{
public:
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