#include "ImageWidget.h"
#include "..\Renderer\DrawingWidgetInterface.h"
#include "..\Renderer\DrawingWidgetInterfaceManager.h"

ImageWidget::ImageWidget()
{
}

void ImageWidget::Render()
{
	UpdateWorldPosition();
	DrawingWidgetInterfaceManager::getInstance().getWidgetDrawingInterface()->RenderImage(*this);
}