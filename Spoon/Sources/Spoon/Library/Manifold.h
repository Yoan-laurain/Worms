#pragma once

class SActor;

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
            SActor* BodyA, SActor* BodyB,
            const FVector2D& Normal, const float Depth,
            const FVector2D& Contact1, const FVector2D& Contact2, const int ContactCount)
            : BodyA(BodyA),
            BodyB(BodyB),
            Normal(Normal),
            Depth(Depth),
            Contact1(Contact1),
            Contact2(Contact2),
            ContactCount(ContactCount)
        {
        }

        Manifold& operator=(const Manifold& Other)
        {
            if (this == &Other)
                return *this;

            BodyA = Other.BodyA;
            BodyB = Other.BodyB;
            Normal = Other.Normal;
            Depth = Other.Depth;
            Contact1 = Other.Contact1;
            Contact2 = Other.Contact2;
            ContactCount = Other.ContactCount;

            return *this;
        }
};
