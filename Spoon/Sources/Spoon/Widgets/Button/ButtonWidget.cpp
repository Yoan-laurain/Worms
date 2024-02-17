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
	: SelectedStyle( { FColor(127, 127, 127, 255), FColor(255, 255, 255, 255), 2.f } )
	, OnClick(nullptr)
	, bIsSelected(false)
	, textBlock(nullptr)
{
}

void ButtonWidget::Render()
{
	UpdateWorldPosition();

	DrawingWidgetInterfaceManager::getInstance().getWidgetDrawingInterface()->RenderButton(*this);

	if (!dynamic_cast<ImGuiWidgetRenderer*>(DrawingWidgetInterfaceManager::getInstance().getWidgetDrawingInterface().get()))
	{
		if (textBlock)
		{
			textBlock->FontSize = 10.f;
			textBlock->RelativePosition = FVector2D(Size.X / 2.f - (textBlock->Text.size() / 2.f * textBlock->FontSize / 2.f),
				Size.Y / 2.f - textBlock->FontSize / 2.f);
			textBlock->color = FColor(255, 255, 255, 255);
			textBlock->Render();
		}

		if (image)
		{
			image->Size = Size;
			image->Render();
		}
	}
}

void ButtonWidget::CallOnClick()
{
	bIsSelected = !bIsSelected;
	if ( OnClick )
	{
		OnClick(); 
	}
}

void ButtonWidget::SetText(const std::string& text)
{
	if ( !textBlock )
	{		
		TextBlockWidget* TBWidget = WidgetHandler::CreateWidget<TextBlockWidget>(this);
		textBlock = std::unique_ptr<TextBlockWidget>(TBWidget);
	}
	textBlock->Text = text;
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

		imgWidget->ImagePath = imagePath;
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

Style& ButtonWidget::GetStyle() const
{
	if (bIsSelected)
	{
		return const_cast<Style&>(SelectedStyle);
	}
	
	return Widget::GetStyle();
}