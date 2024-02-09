#pragma once

#include "Objects/SObject.h"
#include "WidgetManager.h"
#include <vector>
#include <memory>
#include <Library/TVector.h>
#include <Library/TColor.h>

enum class Visibility 
{
    VISIBLE,
    HIDDEN,
    COLLAPSED
};

class DrawingInterface;
class Window;

class SPOON_API Widget : public SObject
{
    public:
        Widget();
        virtual ~Widget() = default;

        virtual void render(Window* window) = 0;

        void AddToViewport();
        void RemoveFromParent();

        void SetIsEnabled(bool bIsEnabled);
        void SetVisibility(Visibility visibility);

        void SetParent(std::unique_ptr<SObject> parent);

        void SetRelativePosition(FVector2D position);
        void SetSize(FVector2D size);
        void UpdateWorldPosition();
        bool IsPointInWidget( const FVector2D& mousePosition);
        void SetBackgroundColor(FColor color);

        bool bIsAddedToViewport;
        bool bIsEnabled;
        Visibility visibility;

        std::unique_ptr<SObject> parent;

        FVector2D relativePosition;
        FVector2D worldPosition;
        FVector2D size;
        FColor BackgroundColor;
};