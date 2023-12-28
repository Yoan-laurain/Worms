#pragma once

#include "Spoon/Library/Collision.h"
#include <snpch.h>


template <typename T>
struct CollisionShape
{
	using ShapeType = T;

	CollisionShape() : Body(nullptr) {};

	CollisionShape(ShapeType* body)
		: Body(body)
	{}

	template <typename OtherShapeType>
	bool CheckCollisionImpl(const CollisionShape<OtherShapeType>& other) const { return false; };

	bool CheckCollisionImpl(const CollisionShape<ShapeType>& other) const { return false; };

	ShapeType* Body;
};

struct BaseShape;
struct CircleShape;
struct PolygonShape;
using BaseShapeCollision = CollisionShape<BaseShape>;
using CircleShapeCollision = CollisionShape<CircleShape>;
using PolygonShapeCollision = CollisionShape<PolygonShape>;

struct BaseShape
{
    BaseShape(const FVector2D& _center) : Center(_center) { tmp = BaseShapeCollision(this); }

    FVector2D Center;

    BaseShapeCollision tmp;
};

struct CircleShape : public BaseShape
{
    CircleShape(const FVector2D& _center, float _radius) : BaseShape(_center), Radius(_radius) { tmp = CircleShapeCollision(this); }

    float Radius;

    CircleShapeCollision tmp;
};

struct PolygonShape : public BaseShape
{
    PolygonShape(const FVector2D& _center, const std::vector<FVector2D> _vertices) : BaseShape(_center), Vertices(_vertices) { tmp = PolygonShapeCollision(this); }

    std::vector<FVector2D> Vertices;

	PolygonShapeCollision tmp;
};

template <>
template <>
inline bool CollisionShape<CircleShape>::CheckCollisionImpl<PolygonShape>(const CollisionShape<PolygonShape>& other) const
{
    FVector2D normal;
    float depth;
    return Collision::IntersectCirclePolygon(Body->Center, Body->Radius, other.Body->Center , other.Body->Vertices, normal, depth);
}

template <>
inline bool CollisionShape<CircleShape>::CheckCollisionImpl(const CollisionShape<CircleShape>& other) const
{
    FVector2D normal;
    float depth;
    return Collision::IntersectCircles(Body->Center, Body->Radius, other.Body->Center, other.Body->Radius, normal, depth);
}

template <>
inline bool CollisionShape<PolygonShape>::CheckCollisionImpl(const CollisionShape<PolygonShape>& other) const
{
    FVector2D normal;
    float depth;
    return Collision::IntersectPolygons(Body->Vertices, other.Body->Vertices, normal, depth);
}