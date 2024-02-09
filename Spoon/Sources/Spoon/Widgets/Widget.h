#pragma once

#include "Objects/SObject.h"
#include "WidgetManager.h"
#include "Library/TVector.h"
#include "Library/TColor.h"
#include <memory>

enum class Visibility 
{
    VISIBLE,
    HIDDEN,
    COLLAPSED
};

class DrawingWidgetInterface;
class Window;

class SPOON_API Widget : public SObject
{
    public:
        Widget();
        ~Widget() override = default;

        virtual void render() = 0;

        void AddToViewport();
        void RemoveFromParent();

        void SetParent(std::unique_ptr<SObject> parent);
    
        void UpdateWorldPosition();
        bool IsPointInWidget( const FVector2D& mousePosition);

        bool bIsAddedToViewport;
        bool bIsEnabled;
        Visibility visibility;

        std::unique_ptr<SObject> parent;

        FVector2D relativePosition;
        FVector2D worldPosition;
        FVector2D size;
        FColor BackgroundColor;
};