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

    void AddWidget(std::shared_ptr<Widget> widget);
    void RemoveWidget(Widget* child);
    void GetWidgetToRender();
    void HandleWidgetOnClicked(const FVector2D& mousePosition);
    void HandleWidgetHoverState(const FVector2D& mousePosition, bool& bIsHoveringSomething);

    void BeforeRenderImGui();
    void AfterRenderImGui();

    private:
        void UnSelectAllOtherButtons(Widget* widget);

	private:
		std::vector< std::shared_ptr<Widget> > Widgets;

        static WidgetManager* instance;
};