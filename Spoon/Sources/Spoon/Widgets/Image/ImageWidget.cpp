#include "ImageWidget.h"
#include "..\Renderer\DrawingWidgetInterface.h"
#include "Core/Window.h"
#include "..\Renderer\DrawingWidgetInterfaceManager.h"

ImageWidget::ImageWidget() : imagePath("")
{
}

void ImageWidget::render()
{
	UpdateWorldPosition();
	DrawingWidgetInterfaceManager::getInstance().getWidgetDrawingInterface()->RenderImage(imagePath, worldPosition, size);
}