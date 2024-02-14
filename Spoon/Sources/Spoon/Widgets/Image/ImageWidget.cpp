#include "ImageWidget.h"
#include "..\Renderer\DrawingWidgetInterface.h"
#include "Core/Window.h"
#include "..\Renderer\DrawingWidgetInterfaceManager.h"

ImageWidget::ImageWidget() : ImagePath("")
{
}

void ImageWidget::Render()
{
	UpdateWorldPosition();
	DrawingWidgetInterfaceManager::getInstance().getWidgetDrawingInterface()->RenderImage(*this);
}