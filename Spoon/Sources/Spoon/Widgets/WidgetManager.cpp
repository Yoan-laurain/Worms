#include "WidgetManager.h"
#include "Widget.h"
#include "Objects/SActor.h"
#include "Button/ButtonWidget.h"
#include <Core/Window.h>

WidgetManager* WidgetManager::instance = nullptr;

WidgetManager::WidgetManager() : Widgets()
{
}

WidgetManager* WidgetManager::GetInstance()
{
    if (instance == nullptr)
	{
		instance = new WidgetManager();
	}
	return instance;
}

void WidgetManager::AddWidget(std::shared_ptr<Widget> widget)
{
	Widgets.push_back(widget);
}

void WidgetManager::RemoveWidget(Widget* child)
{
	auto it = std::find_if(Widgets.begin(), Widgets.end(), [child](std::shared_ptr<Widget> widget) { return widget.get() == child; });
	if (it != Widgets.end())
	{
		Widgets.erase(it);
	}
}

void WidgetManager::RenderWidgets(Window* window)
{
	for (auto& widget : Widgets)
	{
		if (widget.get()->bIsAddedToViewport)
		{
			widget.get()->render(window); 
		}
	}
}

void WidgetManager::HandleWidgetOnClicked(const FVector2D& mousePosition)
{
	for (auto& widget : Widgets)
	{
		if (widget.get()->bIsAddedToViewport)
		{
			if (widget.get()->IsPointInWidget(mousePosition))
			{
				ButtonWidget* button = dynamic_cast<ButtonWidget*>(widget.get());
				if (button)
				{
					button->OnClick(); 
				}
			}
		}
	}
}
