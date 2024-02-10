#include "WidgetManager.h"
#include "Widget.h"
#include "Objects/SActor.h"
#include "Button/ButtonWidget.h"
#include "Core/Window.h"
#include "Renderer\DrawingWidgetInterfaceManager.h"
#include "Renderer\ImGui\ImGuiWidgetRenderer.h"
#include <imgui.h>
#include <SFML/Graphics/Drawable.hpp>

WidgetManager* WidgetManager::instance = nullptr;

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

void WidgetManager::GetWidgetToRender()
{
	if (dynamic_cast<ImGuiWidgetRenderer*>(DrawingWidgetInterfaceManager::getInstance().getWidgetDrawingInterface().get()))
	{
		BeforeRenderImGui();
	}

	for (auto& widget : Widgets)
	{
		if (widget.get() && widget.get()->bIsAddedToViewport)
		{
			widget.get()->render();
		}
	}

	if (dynamic_cast<ImGuiWidgetRenderer*>(DrawingWidgetInterfaceManager::getInstance().getWidgetDrawingInterface().get()))
	{
		AfterRenderImGui();
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

void WidgetManager::BeforeRenderImGui()
{
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
	
	ImGui::Begin("Widgets", NULL,
				ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoFocusOnAppearing |
			ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoDecoration);
}

void WidgetManager::AfterRenderImGui()
{
	ImGui::End();
}