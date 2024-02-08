#include "ProgressBarWidget.h"
#include "../Renderer/DrawingInterface.h"
#include "Core/Window.h"

ProgressBarWidget::ProgressBarWidget() : progress(0.0f)
{
}

void ProgressBarWidget::render(Window* window)
{
	if (!renderer.expired())
	{
		UpdateWorldPosition();
		renderer.lock()->RenderProgressBar(window,worldPosition, size, progress, color, backgroundColor);
	}
}

void ProgressBarWidget::setProgress(float progress)
{
	this->progress = progress;
}

void ProgressBarWidget::setColor(const FColor& color)
{
	this->color = color;
}

void ProgressBarWidget::setBackgroundColor(const FColor& color)
{
	this->backgroundColor = color;
}