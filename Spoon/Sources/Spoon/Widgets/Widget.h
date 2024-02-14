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

        virtual void Render() = 0;

        void AddToViewport();
        void RemoveFromParent();

        void SetParent(SObject* parent);
    
        void UpdateWorldPosition();
        bool IsPointInWidget( const FVector2D& mousePosition);

        bool IsHovered() const;
        void OnHover();
        void OnUnhover();
        virtual void Tick(float deltaTime);

        virtual void SetIsEnabled(bool bIsEnabled);
        bool IsEnabled() const;

        bool bIsAddedToViewport;
        bool bIsTickable;

        Visibility visibility;

        SObject* parent;

        FVector2D RelativePosition;
        FVector2D worldPosition;
        FVector2D Size;
        float Rotation;
        FColor BackgroundColor;
        std::function<void()> onHover;

        bool IsMarkedForDestruction;

    private:
        bool bIsHovered;
        bool bIsEnabled;
};