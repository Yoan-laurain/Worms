#include "ButtonWidget.h"
#include "../TextBlock/TextBlockWidget.h"
#include "..\Renderer\DrawingWidgetInterface.h"
#include "Core/Window.h"
#include "Objects/SActor.h"
#include "Library/WidgetHandler.h"
#include "Widgets/Image/ImageWidget.h"
#include "..\Renderer\DrawingWidgetInterfaceManager.h"
#include "..\Renderer\ImGui\ImGuiWidgetRenderer.h"

ButtonWidget::ButtonWidget() 
	: onClick(nullptr)
	, textBlock(nullptr)
	, bIsSelected(false)
{
}

void ButtonWidget::render()
{
	UpdateWorldPosition();

	DrawingWidgetInterfaceManager::getInstance().getWidgetDrawingInterface()->RenderButton(*this);

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

		if (image)
		{
			image->size = size;
			image->render();
		}
	}
}

void ButtonWidget::OnClick()
{
	bIsSelected = !bIsSelected;
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

void ButtonWidget::SetBackgroundImage(const std::string& imagePath)
{
	if (!image)
	{
		ImageWidget* imgWidget = WidgetHandler::CreateWidget<ImageWidget>(this);

		if (!imgWidget)
		{
			return;
		}

		imgWidget->imagePath = imagePath;
		image = std::unique_ptr<ImageWidget>(imgWidget);
	}
}

void ButtonWidget::SetIsEnabled(bool bIsEnabled)
{
	Widget::SetIsEnabled(bIsEnabled);
	 
	if (!bIsEnabled)
	{
		bIsSelected = false;
	}
}

ImageWidget* ButtonWidget::GetImage() const
{
	return image.get();
}

TextBlockWidget* ButtonWidget::GetTextBlock() const
{
	return textBlock.get();
}
