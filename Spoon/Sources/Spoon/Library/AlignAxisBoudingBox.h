#include <iostream>
#include "Core/Core.h"
#include "TVector.h"

class OBJECT_API AlignAxisBoundingBox
{
public:
    const FVector2D Min;
    const FVector2D Max;

    AlignAxisBoundingBox(const FVector2D& min, const FVector2D& max) : Min(min), Max(max) {} 

    AlignAxisBoundingBox(float minX, float minY, float maxX, float maxY) : Min(minX, minY), Max(maxX, maxY) {} 

    AlignAxisBoundingBox& operator=(const AlignAxisBoundingBox& other)
    {
        if (this == &other)
            return *this;

        const_cast<FVector2D&>(Min) = other.Min;
        const_cast<FVector2D&>(Max) = other.Max;

        return *this;
    }
};