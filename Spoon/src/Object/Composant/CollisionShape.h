#pragma once

class CollisionShape
{
public:
    virtual ~CollisionShape() = 0;

    bool CheckCollision(const CollisionShape& other);
};

class CircleCollision : public CollisionShape
{
    public:
        CircleCollision(FVector2D center, float radius);

        FVector2D center;
        float radius;
};

class PolygonCollision : public CollisionShape
{
    public:
	    PolygonCollision(std::vector<FVector2D> vertices, FVector2D center);

	    std::vector<FVector2D> vertices;
        FVector2D center;
};

class CollisionChecker
{
    public :

	    static bool CheckCollision(const CollisionShape& shape1, const CollisionShape& shape2);

private :

	    static bool CheckCollision(const CircleCollision& circle1, const CircleCollision& circle2);
        static bool CheckCollision(const PolygonCollision& polygon1, const PolygonCollision& polygon2);

        static bool CheckCollision(const CircleCollision& circle, const PolygonCollision& polygon);

};