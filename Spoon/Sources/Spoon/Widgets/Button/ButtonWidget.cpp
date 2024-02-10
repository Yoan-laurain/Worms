#include "ButtonWidget.h"
#include "../TextBlock/TextBlockWidget.h"
#include "..\Renderer\DrawingWidgetInterface.h"
#include "Core/Window.h"
#include "Objects/SActor.h"
#include "Library/WidgetHandler.h"
#include "..\Renderer\DrawingWidgetInterfaceManager.h"
#include "..\Renderer\ImGui\ImGuiWidgetRenderer.h"

ButtonWidget::ButtonWidget() :
	onClick(nullptr),
	textBlock(nullptr)
{
}

void ButtonWidget::render()
{
	UpdateWorldPosition();

	DrawingWidgetInterfaceManager::getInstance().getWidgetDrawingInterface()->RenderButton(worldPosition, size, textBlock->text, BackgroundColor);

	if (!dynamic_cast<ImGuiWidgetRenderer*>(DrawingWidgetInterfaceManager::getInstance().getWidgetDrawingInterface().get()))
	{
		if (textBlock)
		{
			textBlock->fontSize = 10.f;
			textBlock->relativePosition = FVector2D(size.X / 2.f - (textBlock->text.size() / 2.f * textBlock->fontSize / 2.f),
				size.Y / 2.f - textBlock->fontSize / 2.f);
			textBlock->color = FColor(255, 255, 255, 255);
			textBlock->render();
		}
	}
}

void ButtonWidget::OnClick()
{
	if ( onClick )
	{
		onClick(); 
	}
}

void ButtonWidget::SetText(const std::string& text)
{
	if ( !textBlock )
	{		
		TextBlockWidget* TBWidget = WidgetHandler::CreateWidget<TextBlockWidget>(this);
		textBlock = std::unique_ptr<TextBlockWidget>(TBWidget);
	}
	textBlock->text = text;
}