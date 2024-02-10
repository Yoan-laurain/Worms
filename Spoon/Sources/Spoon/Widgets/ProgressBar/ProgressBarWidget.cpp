#include "ProgressBarWidget.h"
#include "..\Renderer\DrawingWidgetInterface.h"
#include "Core/Window.h"
#include "..\Renderer\DrawingWidgetInterfaceManager.h"

ProgressBarWidget::ProgressBarWidget() :
	progress(0.0f),
	color(FColor::White())
{
}

void ProgressBarWidget::render()
{
	UpdateWorldPosition();
	DrawingWidgetInterfaceManager::getInstance().getWidgetDrawingInterface()->RenderProgressBar(worldPosition, size, progress, color, BackgroundColor);
}