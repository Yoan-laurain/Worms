#include "TextBlockWidget.h"
#include "..\Renderer\DrawingWidgetInterface.h"
#include "..\Renderer\DrawingWidgetInterfaceManager.h"

TextBlockWidget::TextBlockWidget() :
	FontSize(1.0f),
	color(FColor::White())
{
	
}

void TextBlockWidget::Render()
{
	UpdateWorldPosition();
	DrawingWidgetInterfaceManager::GetInstance().GetWidgetDrawingInterface()->RenderText(*this);
}