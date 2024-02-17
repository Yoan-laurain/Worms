#pragma once

#include "Core/Core.h"
#include "Library/TVector.h"
#include <vector>
#include <memory>

class SObject;
class Widget;

class SPOON_API WidgetManager
{
    public:
        WidgetManager() = default;

        static WidgetManager* GetInstance();

        void AddWidget(std::shared_ptr<Widget> Widget);
        
        void DestroyWidgetMarkedForDestruction();
        void DestroyWidget(const std::shared_ptr<Widget>& Widget);
        
        void RenderWidgets();
        
        void HandleWidgetOnClicked(const FVector2D& MousePosition);
        void HandleWidgetHoverState(const FVector2D& MousePosition, bool& bIsHoveringSomething);

        void BeforeRenderImGui();
        void AfterRenderImGui();

        void Tick(float deltaTime);

    private:
        void UnSelectAllOtherButtons(const Widget* Widget);
    
        std::vector< std::shared_ptr<Widget> > Widgets;

        static WidgetManager* Instance;
};