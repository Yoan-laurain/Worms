#include "WidgetManager.h"
#include "Widget.h"
#include "Objects/SActor.h"
#include "Button/ButtonWidget.h"
#include "Renderer\DrawingWidgetInterfaceManager.h"
#include "Renderer\ImGui\ImGuiWidgetRenderer.h"
#include <imgui.h>

WidgetManager* WidgetManager::Instance = nullptr;

WidgetManager* WidgetManager::GetInstance()
{
    if (Instance == nullptr)
	{
		Instance = new WidgetManager();
	}
	return Instance;
}

void WidgetManager::AddWidget(const std::shared_ptr<Widget>& Widget)
{
	Widgets.push_back(Widget);
}

void WidgetManager::DestroyWidgetMarkedForDestruction()
{
	std::vector<std::shared_ptr<Widget>> WidgetsToDestroy;

	for (auto& Widget : Widgets)
	{
		if (Widget.get()->IsMarkedForDestruction)
		{
			WidgetsToDestroy.push_back(Widget);
		}
	}

	for (auto& Widget : WidgetsToDestroy)
	{
		GetInstance()->DestroyWidget(Widget);
	}
}

void WidgetManager::DestroyWidget(const std::shared_ptr<Widget>& Widget)
{
	auto It = std::find(Widgets.begin(), Widgets.end(), Widget);
	if (It != Widgets.end())
	{
		Widgets.erase(It);
	}
}

void WidgetManager::RenderWidgets()
{
	if (dynamic_cast<ImGuiWidgetRenderer*>(DrawingWidgetInterfaceManager::GetInstance().GetWidgetDrawingInterface().get()))
	{
		BeforeRenderImGui();
	}

	for (auto& Widget : Widgets)
	{
		if (Widget.get() && Widget.get()->bIsAddedToViewport)
		{
			Widget.get()->Render();
		}
	}

	if (dynamic_cast<ImGuiWidgetRenderer*>(DrawingWidgetInterfaceManager::GetInstance().GetWidgetDrawingInterface().get()))
	{
		AfterRenderImGui();
	}
}

void WidgetManager::HandleWidgetOnClicked(const FVector2D& MousePosition)
{
	for (auto& Widget : Widgets)
	{
		if (Widget.get()->bIsAddedToViewport && Widget.get()->IsEnabled() )
		{
			if (Widget.get()->IsPointInWidget(MousePosition))
			{
				ButtonWidget* Button = dynamic_cast<ButtonWidget*>(Widget.get());
				if (Button)
				{
					Button->OnClick();
					Button->bIsSelected = true;
					UnSelectAllOtherButtons(Button);
				}
			}
		}
	}
}

void WidgetManager::HandleWidgetHoverState(const FVector2D& MousePosition, bool& bIsHoveringSomething) 
{
	bIsHoveringSomething = false;
	
	for (auto& Widget : Widgets)
	{
		if (Widget.get()->bIsAddedToViewport && Widget.get()->IsEnabled())
		{
			bIsHoveringSomething = Widget.get()->HandleHoverState(MousePosition) || bIsHoveringSomething;
		}
	}
}

void WidgetManager::UnSelectAllOtherButtons(const Widget* Widget)
{
	for (auto& CurrentWidget : Widgets) 
	{
		if (CurrentWidget.get() != Widget && CurrentWidget.get()->bIsAddedToViewport )
		{
			if (ButtonWidget* Button = dynamic_cast<ButtonWidget*>(CurrentWidget.get()))
			{
				Button->bIsSelected = false;
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

void WidgetManager::Tick(float DeltaTime)
{
	for (auto& Widget : Widgets)
	{
		if (Widget.get()->bIsAddedToViewport && Widget.get()->bIsTickable)
		{
			Widget.get()->Tick(DeltaTime);
		}
	}
}