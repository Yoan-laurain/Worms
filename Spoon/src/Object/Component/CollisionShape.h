#pragma once

#include "Spoon/Library/TVector.h"
#include <vector>

struct SPOON_API BaseShape
{
    BaseShape(const FVector2D _center) : Center(_center) {}
    FVector2D Center;
};

struct SPOON_API CircleShape : public BaseShape
{
    CircleShape(const FVector2D& _center, float _radius) : BaseShape(_center), Radius(_radius) {}

    float Radius;
};

struct SPOON_API PolygonShape : public BaseShape
{
    PolygonShape(const FVector2D& _center, const std::vector<FVector2D> _vertices) : BaseShape(_center), Vertices(_vertices) {}

    std::vector<FVector2D> Vertices;
};
