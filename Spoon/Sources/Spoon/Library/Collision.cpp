#include "Library/Collision.h"
#include <snpch.h>
#include "Manifold.h"

bool Collision::IntersectCirclePolygon(const FVector2D& circleCenter, float circleRadius,
    const FVector2D& polygonCenter, const std::vector<FVector2D>& vertices, FVector2D& normal, float& depth)
{
    normal = FVector2D::Zero();
    depth = std::numeric_limits<float>::max();

    FVector2D axis = FVector2D::Zero();
    float axisDepth = 0.f;
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
        normal.ReverseVector();
    }

    return true;
}

bool Collision::IntersectCircles(const FVector2D& centerA, float radiusA, const FVector2D& centerB, float radiusB, FVector2D& normal, float& depth)
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

void Collision::ApplyCollision(SActor& first, SActor& other, const FVector2D& normal, float depth)
{
    first.bIsColliding = true;
    other.bIsColliding = true;

    if (first.bIsStatic && other.bIsStatic)
    {
        return;
    }

    if (first.bIsStatic)
    {
        other.Move(normal * depth);
    }
    else if (other.bIsStatic)
    {
        first.Move(FVector2D(normal * depth).ReverseVector());
    }
    else
    {
        first.Move(FVector2D(normal * depth / 2.f).ReverseVector());
        other.Move(normal * depth / 2.f);
    }
}

bool Collision::IntersectPolygons(const std::vector<FVector2D>& verticesA, const FVector2D& polygonCenterA, const std::vector<FVector2D>& verticesB, const FVector2D& polygonCenterB, FVector2D& normal, float& depth)
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

    const FVector2D direction = polygonCenterB - polygonCenterA;

    if (FVector2D::DotProduct(direction, normal) < 0.0f)
    {
        normal.ReverseVector();
    }

    return true;
}

void Collision::ProjectVertices(const std::vector<FVector2D>& vertices, const FVector2D& axis, float& min, float& max)
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

void Collision::ProjectCircle(const FVector2D& center, float radius, const FVector2D& axis, float& min, float& max)
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

size_t Collision::FindClosestPointOnPolygon(const FVector2D& circleCenter, const std::vector<FVector2D>& vertices)
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

void Collision::FindContactPoint(const FVector2D& centerA, float radiusA, const FVector2D& centerB, FVector2D& cp)
{
    FVector2D ab = centerB - centerA;
    FVector2D dir = FVector2D::Normalize(ab);
    cp = centerA + dir * radiusA;
}

bool Collision::IntersectAABBs(AlignAxisBoundingBox& a, AlignAxisBoundingBox& b)
{
    if (a.Max.X <= b.Min.X || b.Max.X <= a.Min.X ||
        a.Max.Y <= b.Min.Y || b.Max.Y <= a.Min.Y)
    {
        return false;
    }

    return true;
}
