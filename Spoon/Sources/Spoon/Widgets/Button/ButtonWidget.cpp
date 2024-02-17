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
	, TextBlock(nullptr)
{
}

void ButtonWidget::Render()
{
	UpdateWorldPosition();

	DrawingWidgetInterfaceManager::GetInstance().GetWidgetDrawingInterface()->RenderButton(*this);

	if (!dynamic_cast<ImGuiWidgetRenderer*>(DrawingWidgetInterfaceManager::GetInstance().GetWidgetDrawingInterface().get()))
	{
		if (TextBlock)
		{
			TextBlock->FontSize = 10.f;
			TextBlock->RelativePosition = FVector2D(Size.X / 2.f - (TextBlock->Text.size() / 2.f * TextBlock->FontSize / 2.f),
				Size.Y / 2.f - TextBlock->FontSize / 2.f);
			TextBlock->color = FColor(255, 255, 255, 255);
			TextBlock->Render();
		}

		if (Image)
		{
			Image->Size = Size;
			Image->Render();
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

void ButtonWidget::SetText(const std::string& Text)
{
	if ( !TextBlock )
	{		
		TextBlockWidget* TBWidget = WidgetHandler::CreateWidget<TextBlockWidget>(this);
		TextBlock = std::unique_ptr<TextBlockWidget>(TBWidget);
	}
	TextBlock->Text = Text;
}

void ButtonWidget::SetBackgroundImage(const std::string& ImagePath)
{
	if (!Image)
	{
		ImageWidget* ImgWidget = WidgetHandler::CreateWidget<ImageWidget>(this);

		if (!ImgWidget)
		{
			return;
		}

		ImgWidget->ImagePath = ImagePath;
		Image = std::unique_ptr<ImageWidget>(ImgWidget);
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
	return Image.get();
}

TextBlockWidget* ButtonWidget::GetTextBlock() const
{
	return TextBlock.get();
}

Style& ButtonWidget::GetStyle() const
{
	if (bIsSelected)
	{
		return const_cast<Style&>(SelectedStyle);
	}
	
	return Widget::GetStyle();
}