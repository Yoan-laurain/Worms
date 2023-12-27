#pragma once

#include "snpch.h"
#include <Spoon/Library/Collision.h>

struct ShapeOfYou
{
    ShapeOfYou() {};
    virtual ~ShapeOfYou() {};
};

struct CircleCollision : public ShapeOfYou
{
    CircleCollision(const FVector2D& center, float radius)
        : center(center)
        , radius(radius)
    {
    }

    FVector2D center;
    float radius;
};

struct PolygonCollision : public ShapeOfYou
{
    PolygonCollision(const std::vector<FVector2D>& vertices)
        : vertices(vertices)
    {
    }

    std::vector<FVector2D> vertices;
    FVector2D center;
};

template <typename ShapeType>
struct CollisionShape
{    
    CollisionShape(const ShapeType& body)
        : Body(body)
    {
	}

    template <typename OtherShapeType>
    bool CheckCollisionImpl(const OtherShapeType& other) const { return false; };

    bool CheckCollisionImpl(const ShapeType& other) const { return false; };

    using Type = ShapeType;

    Type Body;
};

template <>
template <>
inline bool CollisionShape<CircleCollision>::CheckCollisionImpl<PolygonCollision>(const PolygonCollision& other) const
{
    FVector2D normal;
    float depth;
    return Collision::IntersectCirclePolygon(Body.center, Body.radius, other.center, other.vertices, normal, depth);
}

template <>
inline bool CollisionShape<CircleCollision>::CheckCollisionImpl(const CircleCollision& other) const
{
    FVector2D normal;
    float depth;
    return Collision::IntersectCircles(Body.center, Body.radius, other.center, other.radius, normal, depth);
}

template <>
inline bool CollisionShape<PolygonCollision>::CheckCollisionImpl(const PolygonCollision& other) const
{
    FVector2D normal;
    float depth;
    return Collision::IntersectPolygons(Body.vertices, other.vertices, normal, depth);
}

using BasicCollisionShape = CollisionShape<ShapeOfYou>;
using CircleCollisionShape = CollisionShape<CircleCollision>;
using PolygonCollisionShape = CollisionShape<PolygonCollision>;