#pragma once

#include "Core/Core.h"
#include "Library/TVector.h"
#include <vector>
#include <memory>

class SObject;
class Widget;
class Window;

class SPOON_API WidgetManager
{
    public:
        WidgetManager();

    static WidgetManager* GetInstance();

    void AddWidget(std::shared_ptr<Widget> widget);
    void RemoveWidget(Widget* child);
    void RenderWidgets(Window* window);
    void HandleWidgetOnClicked(const FVector2D& mousePosition);

    void BeforeRenderImGui();
    void AfterRenderImGui();

	private:
		std::vector< std::shared_ptr<Widget> > Widgets;

        static WidgetManager* instance;
};