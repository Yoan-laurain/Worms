#include "TextBlockWidget.h"
#include "../Renderer/DrawingInterface.h"
#include "Core/Window.h"
#include <Objects/SActor.h>
#include <Widgets/Renderer/DrawingInterfaceManager.h>

TextBlockWidget::TextBlockWidget() : 
	Widget(),
	text(""),
	color(),
	fontSize(1.0f)
{
	
}

void TextBlockWidget::render(Window* window)
{
	UpdateWorldPosition();
	DrawingInterfaceManager::getInstance().getDrawingInterface()->RenderText(window,text, worldPosition, fontSize, color);
}

void TextBlockWidget::setText(const std::string& text)
{
	this->text = text;
}

void TextBlockWidget::setColor(const FColor color)
{
	this->color = color;
}

void TextBlockWidget::setFontSize(float fontSize)
{
	this->fontSize = fontSize;
}