#include "Spoon/Core/Core.h"
#include "Spoon/Library/TVector.h"
#include "Spoon/Library/Collision.h"

#include <Object/Composant/CollisionShape.h>

bool CollisionShape::CheckCollision(const CollisionShape& other)
{
    CollisionChecker::CheckCollision(*this, other);
}

CircleCollision::CircleCollision(FVector2D center, float radius) : center(center), radius(radius)
{
}

PolygonCollision::PolygonCollision(std::vector<FVector2D> vertices, FVector2D center) : vertices(vertices), center(center)
{
}

bool CollisionChecker::CheckCollision(const CollisionShape& a, const CollisionShape& b)
{
	return CollisionChecker::CheckCollision(a, b);
}

bool CollisionChecker::CheckCollision(const CircleCollision& circle1, const CircleCollision& circle2)
{
    FVector2D normal;
    float depth;
    return Collision::IntersectCircles(circle1.center, circle1.radius, circle2.center, circle2.radius, normal, depth);
}

bool CollisionChecker::CheckCollision(const CircleCollision& circle, const PolygonCollision& polygon)
{
    FVector2D normal;
    float depth;
    return Collision::IntersectCirclePolygon(circle.center, circle.radius, polygon.center, polygon.vertices, normal, depth);
}

bool CollisionChecker::CheckCollision(const PolygonCollision& polygon1, const PolygonCollision& polygon2)
{
    FVector2D normal;
    float depth;
    return Collision::IntersectPolygons(polygon1.vertices,polygon2.vertices, normal, depth);
}