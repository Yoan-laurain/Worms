#include "ProgressBarWidget.h"

ProgressBarWidget::ProgressBarWidget() : progress(0.0f)
{
}

void ProgressBarWidget::render()
{
}

void ProgressBarWidget::setProgress(float progress)
{
	this->progress = progress;
}