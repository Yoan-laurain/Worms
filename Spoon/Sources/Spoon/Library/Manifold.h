#pragma once

#include <Objects/SActor.h>

class OBJECT_API Manifold
{
public:
    SActor* BodyA;
    SActor* BodyB;
    FVector2D Normal;
    float Depth;
    FVector2D Contact1;
    FVector2D Contact2;
    int ContactCount;

    Manifold()
        : BodyA(nullptr),
        BodyB(nullptr),
        Normal(FVector2D::Zero()),
        Depth(0.f),
        Contact1(FVector2D::Zero()),
        Contact2(FVector2D::Zero()),
        ContactCount(0)
    {
    }

    Manifold(
        SActor* bodyA, SActor* bodyB,
         FVector2D& normal, float depth,
         FVector2D& contact1,  FVector2D& contact2, int contactCount)
        : BodyA(bodyA),
        BodyB(bodyB),
        Normal(normal),
        Depth(depth),
        Contact1(contact1),
        Contact2(contact2),
        ContactCount(contactCount)
    {
    }

    Manifold& operator=( Manifold& other)
    {
        if (this == &other)
            return *this;

        BodyA = other.BodyA;
        BodyB = other.BodyB;
        Normal = other.Normal;
        Depth = other.Depth;
        Contact1 = other.Contact1;
        Contact2 = other.Contact2;
        ContactCount = other.ContactCount;

        return *this;
    }
};
