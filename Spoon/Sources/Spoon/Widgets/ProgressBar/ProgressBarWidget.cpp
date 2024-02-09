#include "ProgressBarWidget.h"
#include "..\Renderer\DrawingWidgetInterface.h"
#include "Core/Window.h"
#include "..\Renderer\DrawingWidgetInterfaceManager.h"

ProgressBarWidget::ProgressBarWidget() :
	progress(0.0f),
	color(FColor::White())
{
}

void ProgressBarWidget::render(Window* window)
{
	UpdateWorldPosition();
	DrawingWidgetInterfaceManager::getInstance().getWidgetDrawingInterface()->RenderProgressBar(window,worldPosition, size, progress, color, BackgroundColor);
}