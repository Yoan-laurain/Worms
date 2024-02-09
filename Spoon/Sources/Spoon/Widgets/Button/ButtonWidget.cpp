#include "ButtonWidget.h"
#include "../TextBlock/TextBlockWidget.h"
#include "../Renderer/DrawingInterface.h"
#include "Core/Window.h"
#include <Objects/SActor.h>
#include <Library/WidgetHandler.h>
#include <Widgets/Renderer/DrawingInterfaceManager.h>
#include <Widgets/Renderer/ImGui/ImGuiRenderer.h>

ButtonWidget::ButtonWidget()
{
}

void ButtonWidget::render(Window* window)
{
	UpdateWorldPosition();

	DrawingInterfaceManager::getInstance().getDrawingInterface()->RenderButton(window,worldPosition, size, textBlock->text);

	if (!dynamic_cast<ImGuiRenderer*>(DrawingInterfaceManager::getInstance().getDrawingInterface().get()))
	{
		if (textBlock)
		{
			textBlock->setFontSize(10.f);
			textBlock->SetRelativePosition(FVector2D(size.X / 2.f - (textBlock->text.size() / 2.f * textBlock->fontSize / 2.f),
				size.Y / 2.f - textBlock->fontSize / 2.f));
			textBlock->setColor(FColor(255, 255, 255, 255));
			textBlock->render(window);
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
	textBlock->setText(text);
}

void ButtonWidget::SetOnClick(std::function<void()> onClick)
{
	this->onClick = onClick;
}