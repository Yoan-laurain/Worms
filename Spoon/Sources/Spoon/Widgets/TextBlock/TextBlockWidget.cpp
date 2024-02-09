#include "TextBlockWidget.h"
#include "..\Renderer\DrawingWidgetInterface.h"
#include "Core/Window.h"
#include "..\Renderer\DrawingWidgetInterfaceManager.h"

TextBlockWidget::TextBlockWidget() :
	fontSize(1.0f),
	text(""),
	color(FColor::White())
{
	
}

void TextBlockWidget::render(Window* window)
{
	UpdateWorldPosition();
	DrawingWidgetInterfaceManager::getInstance().getWidgetDrawingInterface()->RenderText(window,text, worldPosition, fontSize, color);
}