#include "Library/Collision.h"
#include "Manifold.h"
#include <snpch.h>

bool Collision::IntersectCirclePolygon(const FVector2D& CircleCenter, float CircleRadius,
    const FVector2D& polygonCenter, const std::vector<FVector2D>& Vertices, FVector2D& Normal, float& Depth)
{
    Normal = FVector2D::Zero();
    Depth = std::numeric_limits<float>::max();

    FVector2D Axis = FVector2D::Zero();
    float AxisDepth = 0.f;
    float MinA, MaxA, MinB, MaxB;

    for (size_t i = 0; i < Vertices.size(); ++i)
    {
        const FVector2D& Va = Vertices[i];
        const FVector2D& Vb = Vertices[(i + 1) % Vertices.size()];

        const FVector2D Edge = Vb - Va;
        Axis = FVector2D(-Edge.Y, Edge.X);
        Axis = FVector2D::Normalize(Axis);

        ProjectVertices(Vertices, Axis, MinA, MaxA);
        ProjectCircle(CircleCenter, CircleRadius, Axis, MinB, MaxB);

        if (MinA >= MaxB || MinB >= MaxA)
        {
            return false;
        }

        AxisDepth = std::min(MaxB - MinA, MaxA - MinB);

        if (AxisDepth < Depth)
        {
            Depth = AxisDepth;
            Normal = Axis;
        }
    }

    size_t CpIndex = FindClosestPointOnPolygon(CircleCenter, Vertices);
    const FVector2D& Cp = Vertices[CpIndex];

    Axis = Cp - CircleCenter;
    Axis = FVector2D::Normalize(Axis);

    ProjectVertices(Vertices, Axis, MinA, MaxA);
    ProjectCircle(CircleCenter, CircleRadius, Axis, MinB, MaxB);

    if (MinA >= MaxB || MinB >= MaxA)
    {
        return false;
    }

    AxisDepth = std::min(MaxB - MinA, MaxA - MinB);

    if (AxisDepth < Depth)
    {
        Depth = AxisDepth;
        Normal = Axis;
    }

    const FVector2D Direction = polygonCenter - CircleCenter;

    if (FVector2D::DotProduct(Direction, Normal) < 0.0f)
    {
        Normal.ReverseVector();
    }

    return true;
}

bool Collision::IntersectCircles(const FVector2D& CenterA, float RadiusA, const FVector2D& CenterB, float RadiusB, FVector2D& Normal, float& Depth)
{
    Normal = FVector2D::Zero();
    Depth = 0.0f;

    const float Distance = FVector2D::Distance(CenterA, CenterB);
    const float Radii = RadiusA + RadiusB;

    if (Distance >= Radii)
    {
        return false;
    }

    Normal = FVector2D::Normalize(CenterB - CenterA);
    Depth = Radii - Distance;

    return true;
}

void Collision::ApplyCollision(SActor& First, SActor& Other, const FVector2D& Normal, float Depth)
{
    First.bIsColliding = true;
    Other.bIsColliding = true;

    if (First.bIsStatic && Other.bIsStatic)
    {
        return;
    }

    if (First.bIsStatic)
    {
        Other.Move(Normal * Depth);
    }
    else if (Other.bIsStatic)
    {
        First.Move(FVector2D(Normal * Depth).ReverseVector());
    }
    else
    {
        First.Move(FVector2D(Normal * Depth / 2.f).ReverseVector());
        Other.Move(Normal * Depth / 2.f);
    }
}

bool Collision::IntersectPolygons(const std::vector<FVector2D>& VerticesA, const FVector2D& PolygonCenterA, const std::vector<FVector2D>& VerticesB, const FVector2D& PolygonCenterB, FVector2D& Normal, float& Depth)
{
    Normal = FVector2D::Zero();
    Depth = std::numeric_limits<float>::max();

    for (size_t i = 0; i < VerticesA.size(); ++i)
    {
        const FVector2D& Va = VerticesA[i];
        const FVector2D& Vb = VerticesA[(i + 1) % VerticesA.size()];

        const FVector2D Edge = Vb - Va;
        FVector2D Axis = FVector2D(-Edge.Y, Edge.X);
        Axis = FVector2D::Normalize(Axis);

        float MinA, MaxA, MinB, MaxB;

        ProjectVertices(VerticesA, Axis, MinA, MaxA);
        ProjectVertices(VerticesB, Axis, MinB, MaxB);

        if (MinA >= MaxB || MinB >= MaxA)
        {
            return false;
        }

        const float AxisDepth = std::min(MaxB - MinA, MaxA - MinB);

        if (AxisDepth < Depth)
        {
            Depth = AxisDepth;
            Normal = Axis;
        }
    }

    for (size_t i = 0; i < VerticesB.size(); ++i)
    {
        const FVector2D& Va = VerticesB[i];
        const FVector2D& Vb = VerticesB[(i + 1) % VerticesB.size()];

        const FVector2D Edge = Vb - Va;
        FVector2D Axis = FVector2D(-Edge.Y, Edge.X);
        Axis = FVector2D::Normalize(Axis);

        float MinA, MaxA, MinB, MaxB;

        ProjectVertices(VerticesA, Axis, MinA, MaxA);
        ProjectVertices(VerticesB, Axis, MinB, MaxB);

        if (MinA >= MaxB || MinB >= MaxA)
        {
            return false;
        }

        const float AxisDepth = std::min(MaxB - MinA, MaxA - MinB);

        if (AxisDepth < Depth)
        {
            Depth = AxisDepth;
            Normal = Axis;
        }
    }

    const FVector2D Direction = PolygonCenterB - PolygonCenterA;

    if (FVector2D::DotProduct(Direction, Normal) < 0.0f)
    {
        Normal.ReverseVector();
    }

    return true;
}

void Collision::ProjectVertices(const std::vector<FVector2D>& Vertices, const FVector2D& Axis, float& Min, float& Max)
{
    Min = std::numeric_limits<float>::max();
    Max = std::numeric_limits<float>::min();

    for (const auto& Vertex : Vertices)
    {
        const float Projection = FVector2D::DotProduct(Vertex, Axis);

        if (Projection < Min)
        {
            Min = Projection;
        }

        if (Projection > Max)
        {
            Max = Projection;
        }
    }
}

void Collision::ProjectCircle(const FVector2D& Center, float Radius, const FVector2D& Axis, float& Min, float& Max)
{
    const FVector2D Direction = FVector2D::Normalize(Axis);
    const FVector2D DirectionAndRadius = Direction * Radius;

    const FVector2D P1 = Center + DirectionAndRadius;
    const FVector2D P2 = Center - DirectionAndRadius;

    Min = FVector2D::DotProduct(P1, Axis);
    Max = FVector2D::DotProduct(P2, Axis);

    if (Min > Max)
    {
        std::swap(Min, Max);
    }
}

size_t Collision::FindClosestPointOnPolygon(const FVector2D& CircleCenter, const std::vector<FVector2D>& Vertices)
{
    size_t Result = 0;
    float MinDistance = std::numeric_limits<float>::max();

    for (size_t i = 0; i < Vertices.size(); ++i)
    {
        const FVector2D& V = Vertices[i];
        const float Distance = FVector2D::Distance(V, CircleCenter);

        if (Distance < MinDistance)
        {
            MinDistance = Distance;
            Result = i;
        }
    }

    return Result;
}

void Collision::FindCirclesContactPoint(const FVector2D& CenterA, float RadiusA, const FVector2D& CenterB, FVector2D& Cp)
{
    FVector2D AB = CenterB - CenterA;
    FVector2D Dir = FVector2D::Normalize(AB);
    Cp = CenterA + Dir * RadiusA;
}

bool Collision::IntersectAABBs(AlignAxisBoundingBox& A, AlignAxisBoundingBox& B)
{
    if (A.Max.X <= B.Min.X || B.Max.X <= A.Min.X ||
        A.Max.Y <= B.Min.Y || B.Max.Y <= A.Min.Y)
    {
        return false;
    }

    return true;
}

void Collision::FindCirclePolygonContactPoint(
    const FVector2D& CircleCenter, float CircleRadius,
    const FVector2D& PolygonCenter, const std::vector<FVector2D>& PolygonVertices,
    FVector2D& Cp)
{
    Cp = FVector2D::Zero();

    float MinDistSq = std::numeric_limits<float>::max();

    for (size_t i = 0; i < PolygonVertices.size(); i++)
    {
        const FVector2D& Va = PolygonVertices[i];
        const FVector2D& Vb = PolygonVertices[(i + 1) % PolygonVertices.size()];

        float DistSq;
        FVector2D Contact;
        PointSegmentDistance(CircleCenter, Va, Vb, DistSq, Contact);

        if (DistSq < MinDistSq)
        {
            MinDistSq = DistSq;
            Cp = Contact;
        }
    }
}

void Collision::PointSegmentDistance(const FVector2D& P, const FVector2D& A, const FVector2D& B, float& DistanceSquared, FVector2D& Cp)
{
    FVector2D AB = B - A;
    FVector2D AP = P - A;

    float Proj = FVector2D::DotProduct(AP, AB);
    float AbLenSq = AB.GetSquareLength();
    float D = Proj / AbLenSq;

    if (D <= 0.0f)
    {
        Cp = A;
    }
    else if (D >= 1.0f)
    {
        Cp = B;
    }
    else
    {
        Cp = A + AB * D;
    }

    DistanceSquared = FVector2D::GetSquareLength(P, Cp);
}

void Collision::FindPolygonsContactPoints(
    const std::vector<FVector2D>& VerticesA, const std::vector<FVector2D>& VerticesB,
    FVector2D& Contact1, FVector2D& Contact2, int& ContactCount)
{
    Contact1 = FVector2D::Zero();
    Contact2 = FVector2D::Zero();
    ContactCount = 0;

    float MinDistSq = std::numeric_limits<float>::max();

    for (const auto& P : VerticesA)
    {
        for (size_t j = 0; j < VerticesB.size(); ++j)
        {
            const FVector2D& Va = VerticesB[j];
            const FVector2D& Vb = VerticesB[(j + 1) % VerticesB.size()];

            float DistSq;
            FVector2D Cp;

            PointSegmentDistance(P, Va, Vb, DistSq, Cp);

            if (FVector2D::NearlyEqual(DistSq, MinDistSq))
            {
                if (!FVector2D::NearlyEqual(Cp, Contact1))
                {
                    Contact2 = Cp;
                    ContactCount = 2;
                }
            }
            else if (DistSq < MinDistSq)
            {
                MinDistSq = DistSq;
                ContactCount = 1;
                Contact1 = Cp;
            }
        }
    }

    for (const auto& P : VerticesB)
    {
        for (size_t j = 0; j < VerticesA.size(); ++j)
        {
            const FVector2D& Va = VerticesA[j];
            const FVector2D& Vb = VerticesA[(j + 1) % VerticesA.size()];

            float DistSq;
            FVector2D Cp;

            PointSegmentDistance(P, Va, Vb, DistSq, Cp);

            if (FVector2D::NearlyEqual(DistSq, MinDistSq))
            {
                if (!FVector2D::NearlyEqual(Cp, Contact1))
                {
                    Contact2 = Cp;
                    ContactCount = 2;
                }
            }
            else if (DistSq < MinDistSq)
            {
                MinDistSq = DistSq;
                ContactCount = 1;
                Contact1 = Cp;
            }
        }
    }
}

void Collision::SetCollisionManifold(SActor* First, SActor* Other, Manifold& Collision, FVector2D& Normal, float& Depth,
    FVector2D& Contact1, FVector2D& Contact2, int ContactCount)
{
    Collision.BodyA = First;
    Collision.BodyB = Other;
    Collision.Normal = Normal;
    Collision.Depth = Depth;
    Collision.Contact1 = Contact1;
    Collision.Contact2 = Contact2;
    Collision.ContactCount = ContactCount;
}