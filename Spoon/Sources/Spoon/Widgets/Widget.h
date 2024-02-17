#pragma once

#include "Objects/SObject.h"
#include "WidgetManager.h"
#include "Library/TVector.h"
#include "Library/TColor.h"

enum class Visibility 
{
    VISIBLE,
    HIDDEN,
    COLLAPSED
};

class DrawingWidgetInterface;
class Window;

struct SPOON_API Style
{
    Style (FColor Color, FColor OutlineColor, float OutlineThickness)
        : Color(Color)
        , OutlineColor(OutlineColor)
        , OutlineThickness(OutlineThickness)
    {
        
    }
    
    FColor Color;
    FColor OutlineColor;
    float OutlineThickness;
};

class SPOON_API Widget : public SObject
{
    public:
        Widget();
        virtual ~Widget() override = default;

        virtual void Render() = 0;

        void AddToViewport();
        void RemoveFromParent();

        void SetParent(SObject* Parent);
        bool UpdateWorldPositionRelativeToParent();

        void UpdateWorldPosition();
        bool IsPointInWidget( const FVector2D& MousePosition);

        bool IsHovered() const;
        void OnHover();
        void OnUnhover();

        virtual Style& GetStyle() const;

        virtual void SetIsEnabled(bool bIsEnabled);
        bool IsEnabled() const;

        virtual void Tick(float DeltaTime);
        
        Visibility visibility;

        SObject* Parent;

        FVector2D RelativePosition;
        FVector2D WorldPosition;
        FVector2D Size;
        
        float Rotation;
        
        std::function<void()> onHover;

        Style BaseStyle;
        Style HoverStyle;
        Style DisabledStyle;

        bool IsMarkedForDestruction;
        bool bIsAddedToViewport;
        bool bIsTickable;

    private:
        bool bIsHovered;
        bool bIsEnabled;
};