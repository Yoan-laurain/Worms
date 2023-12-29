#pragma once
#include "Collision.h"
#include "Object/Component/CollisionShape.h"


template <>
inline bool Collision::CheckCollisionImpl<CircleShape, PolygonShape>(struct CircleShape* first, struct PolygonShape* other)
{
	FVector2D normal;
	float depth;
	return Collision::IntersectCirclePolygon(first->Center, first->Radius, other->Center, other->Vertices, normal, depth);
}

template <>
inline bool Collision::CheckCollisionImpl<CircleShape>(CircleShape* first, CircleShape* other)
{
	FVector2D normal;
	float depth;
	return Collision::IntersectCircles(first->Center, first->Radius, other->Center, other->Radius, normal, depth);
}

template <>
inline bool Collision::CheckCollisionImpl<PolygonShape>(PolygonShape* first, PolygonShape* other)
{
	FVector2D normal;
	float depth;
	return Collision::IntersectPolygons(first->Vertices, other->Vertices, normal, depth);
}