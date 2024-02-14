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

void WidgetManager::DestroyWidgetMarkedForDestruction()
{
	std::vector<std::shared_ptr<Widget>> widgetsToDestroy;

	for (auto& widget : Widgets)
	{
		if (widget.get()->IsMarkedForDestruction)
		{
			widgetsToDestroy.push_back(widget);
		}
	}

	for (auto& widget : widgetsToDestroy)
	{
		WidgetManager::GetInstance()->DestroyWidget(widget);
	}
}

void WidgetManager::DestroyWidget(std::shared_ptr<Widget> widget)
{
	auto it = std::find(Widgets.begin(), Widgets.end(), widget);
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
			widget.get()->Render();
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
		if (widget.get()->bIsAddedToViewport && widget.get()->IsEnabled() )
		{
			if (widget.get()->IsPointInWidget(mousePosition))
			{
				ButtonWidget* button = dynamic_cast<ButtonWidget*>(widget.get());
				if (button)
				{
					button->OnClick(); 
					UnSelectAllOtherButtons(button);
				}
			}
		}
	}
}

void WidgetManager::HandleWidgetHoverState(const FVector2D& mousePosition, bool& bIsHoveringSomething) 
{
	bool bIsHovering = false;
	for (auto& widget : Widgets)
	{
		if (widget.get()->bIsAddedToViewport && widget.get()->IsEnabled())
		{
			if ( dynamic_cast<ButtonWidget*>(widget.get()) ) 
			{
				if (widget.get()->IsPointInWidget(mousePosition) && !widget.get()->IsHovered() )
				{
					widget.get()->OnHover();
					bIsHovering = true;
				}
				else if (widget.get()->IsHovered() && !widget.get()->IsPointInWidget(mousePosition))
				{
					widget.get()->OnUnhover(); 
					bIsHovering = false;
				}
				else if (widget.get()->IsHovered() && widget.get()->IsPointInWidget(mousePosition))
				{
					bIsHovering = true;
				}
			}
		}
	}
	bIsHoveringSomething = bIsHovering;
}

void WidgetManager::UnSelectAllOtherButtons(Widget* widget)
{
	for (auto& currentWidget : Widgets)
	{
		if (currentWidget.get() != widget && currentWidget.get()->bIsAddedToViewport )
		{
			if (ButtonWidget* button = dynamic_cast<ButtonWidget*>(currentWidget.get()))
			{
				button->bIsSelected = false;
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

void WidgetManager::Tick(float deltaTime)
{
	for (auto& widget : Widgets)
	{
		if (widget.get()->bIsAddedToViewport && widget.get()->bIsTickable)
		{
			widget.get()->Tick(deltaTime);
		}
	}
}
