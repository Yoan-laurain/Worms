#include "TextBlockWidget.h"
#include "..\Renderer\DrawingWidgetInterface.h"
#include "Core/Window.h"
#include "..\Renderer\DrawingWidgetInterfaceManager.h"

TextBlockWidget::TextBlockWidget() :
	FontSize(1.0f),
	Text(""),
	color(FColor::White())
{
	
}

void TextBlockWidget::Render()
{
	UpdateWorldPosition();
	DrawingWidgetInterfaceManager::getInstance().getWidgetDrawingInterface()->RenderText(*this);
}