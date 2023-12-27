#pragma once

#include <vector>
#include <cmath>
#include <algorithm>
#include "Spoon/Library/TVector.h"

class Collision
{
public:
    static bool IntersectCirclePolygon(const FVector2D& circleCenter, float circleRadius, const FVector2D& polygonCenter,
        const std::vector<FVector2D>& vertices, FVector2D& normal, float& depth)
    {
        normal = FVector2D::Zero();
        depth = std::numeric_limits<float>::max();

        FVector2D axis = FVector2D::Zero();
        float axisDepth = 0.0f;
        float minA, maxA, minB, maxB;

        for (size_t i = 0; i < vertices.size(); ++i)
        {
            const FVector2D& va = vertices[i];
            const FVector2D& vb = vertices[(i + 1) % vertices.size()];

            const FVector2D edge = vb - va;
            axis = FVector2D(-edge.Y, edge.X);
            axis = FVector2D::Normalize(axis);

            ProjectVertices(vertices, axis, minA, maxA);
            ProjectCircle(circleCenter, circleRadius, axis, minB, maxB);

            if (minA >= maxB || minB >= maxA)
            {
                return false;
            }

            axisDepth = std::min(maxB - minA, maxA - minB);

            if (axisDepth < depth)
            {
                depth = axisDepth;
                normal = axis;
            }
        }

        size_t cpIndex = FindClosestPointOnPolygon(circleCenter, vertices);
        const FVector2D& cp = vertices[cpIndex];

        axis = cp - circleCenter;
        axis = FVector2D::Normalize(axis);

        ProjectVertices(vertices, axis, minA, maxA);
        ProjectCircle(circleCenter, circleRadius, axis, minB, maxB);

        if (minA >= maxB || minB >= maxA)
        {
            return false;
        }

        axisDepth = std::min(maxB - minA, maxA - minB);

        if (axisDepth < depth)
        {
            depth = axisDepth;
            normal = axis;
        }

        const FVector2D direction = polygonCenter - circleCenter;

        if (FVector2D::DotProduct(direction, normal) < 0.0f)
        {
            normal -= normal;
        }

        return true;
    }

    static bool IntersectCircles(const FVector2D& centerA, float radiusA,
        const FVector2D& centerB, float radiusB,
        FVector2D& normal, float& depth)
    {
        normal = FVector2D::Zero();
        depth = 0.0f;

        const float distance = FVector2D::Distance(centerA, centerB);
        const float radii = radiusA + radiusB;

        if (distance >= radii)
        {
            return false;
        }

        normal = FVector2D::Normalize(centerB - centerA);
        depth = radii - distance;

        return true;
    }

public:
    static bool IntersectPolygons(const std::vector<FVector2D>& verticesA, const std::vector<FVector2D>& verticesB,
        FVector2D& normal, float& depth)
    {
        normal = FVector2D::Zero();
        depth = std::numeric_limits<float>::max();

        for (size_t i = 0; i < verticesA.size(); ++i)
        {
            const FVector2D& va = verticesA[i];
            const FVector2D& vb = verticesA[(i + 1) % verticesA.size()];

            const FVector2D edge = vb - va;
            FVector2D axis = FVector2D(-edge.Y, edge.X);
            axis = FVector2D::Normalize(axis);

            float minA, maxA, minB, maxB;

            ProjectVertices(verticesA, axis, minA, maxA);
            ProjectVertices(verticesB, axis, minB, maxB);

            if (minA >= maxB || minB >= maxA)
            {
                return false;
            }

            const float axisDepth = std::min(maxB - minA, maxA - minB);

            if (axisDepth < depth)
            {
                depth = axisDepth;
                normal = axis;
            }
        }

        for (size_t i = 0; i < verticesB.size(); ++i)
        {
            const FVector2D& va = verticesB[i];
            const FVector2D& vb = verticesB[(i + 1) % verticesB.size()];

            const FVector2D edge = vb - va;
            FVector2D axis = FVector2D(-edge.Y, edge.X);
            axis = FVector2D::Normalize(axis);

            float minA, maxA, minB, maxB;

            ProjectVertices(verticesA, axis, minA, maxA);
            ProjectVertices(verticesB, axis, minB, maxB);

            if (minA >= maxB || minB >= maxA)
            {
                return false;
            }

            const float axisDepth = std::min(maxB - minA, maxA - minB);

            if (axisDepth < depth)
            {
                depth = axisDepth;
                normal = axis;
            }
        }

        const FVector2D centerA = FindArithmeticMean(verticesA);
        const FVector2D centerB = FindArithmeticMean(verticesB);

        const FVector2D direction = centerB - centerA;

        if (FVector2D::DotProduct(direction, normal) < 0.0f)
        {
            normal -= normal;
        }

        return true;
    }


private:
    static void ProjectVertices(const std::vector<FVector2D>& vertices, const FVector2D& axis, float& min, float& max)
    {
        min = std::numeric_limits<float>::max();
        max = std::numeric_limits<float>::min();

        for (const auto& vertex : vertices)
        {
            const float projection = FVector2D::DotProduct(vertex, axis);

            if (projection < min)
            {
                min = projection;
            }

            if (projection > max)
            {
                max = projection;
            }
        }
    }

    static void ProjectCircle(const FVector2D& center, float radius, const FVector2D& axis, float& min, float& max)
    {
        const FVector2D direction = FVector2D::Normalize(axis);
        const FVector2D directionAndRadius = direction * radius;

        const FVector2D p1 = center + directionAndRadius;
        const FVector2D p2 = center - directionAndRadius;

        min = FVector2D::DotProduct(p1, axis);
        max = FVector2D::DotProduct(p2, axis);

        if (min > max)
        {
            std::swap(min, max);
        }
    }

    static size_t FindClosestPointOnPolygon(const FVector2D& circleCenter, const std::vector<FVector2D>& vertices)
    {
        size_t result = 0;
        float minDistance = std::numeric_limits<float>::max();

        for (size_t i = 0; i < vertices.size(); ++i)
        {
            const FVector2D& v = vertices[i];
            const float distance = FVector2D::Distance(v, circleCenter);

            if (distance < minDistance)
            {
                minDistance = distance;
                result = i;
            }
        }

        return result;
    }

    static FVector2D FindArithmeticMean(const std::vector<FVector2D>& vertices)
    {
        float sumX = 0.0f;
        float sumY = 0.0f;

        for (const FVector2D& v : vertices)
        {
            sumX += v.X;
            sumY += v.Y;
        }

        return FVector2D(sumX / static_cast<float>(vertices.size()), sumY / static_cast<float>(vertices.size()));
    }
};