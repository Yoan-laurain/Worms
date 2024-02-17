#pragma once

#include "Core/Core.h"
#include "TVector.h"

class OBJECT_API AlignAxisBoundingBox
{
    public:
        const FVector2D Min;
        const FVector2D Max;

        AlignAxisBoundingBox(const FVector2D& Min, const FVector2D& Max) : Min(Min), Max(Max) {} 

        AlignAxisBoundingBox(float MinX, float MinY, float MaxX, float MaxY) : Min(MinX, MinY), Max(MaxX, MaxY) {} 

        AlignAxisBoundingBox& operator=(const AlignAxisBoundingBox& Other)
        {
            if (this == &Other)
                return *this;

            const_cast<FVector2D&>(Min) = Other.Min;
            const_cast<FVector2D&>(Max) = Other.Max;

            return *this;
        }
};