#include "ImageWidget.h"
#include "..\Renderer\DrawingWidgetInterface.h"
#include "..\Renderer\DrawingWidgetInterfaceManager.h"

void ImageWidget::Render()
{
	UpdateWorldPosition();
	DrawingWidgetInterfaceManager::GetInstance().GetWidgetDrawingInterface()->RenderImage(*this);
}