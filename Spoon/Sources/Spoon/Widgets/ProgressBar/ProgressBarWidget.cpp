#include "ProgressBarWidget.h"
#include "../Renderer/DrawingInterface.h"
#include "Core/Window.h"
#include <Widgets/Renderer/DrawingInterfaceManager.h>

ProgressBarWidget::ProgressBarWidget() : progress(0.0f)
{
}

void ProgressBarWidget::render(Window* window)
{
	UpdateWorldPosition();
	DrawingInterfaceManager::getInstance().getDrawingInterface()->RenderProgressBar(window,worldPosition, size, progress, color, BackgroundColor);
}

void ProgressBarWidget::setProgress(float progress)
{
	this->progress = progress;
}

void ProgressBarWidget::setColor(const FColor& color)
{
	this->color = color;
}