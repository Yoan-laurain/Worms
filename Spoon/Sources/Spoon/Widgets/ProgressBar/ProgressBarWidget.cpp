#include "ProgressBarWidget.h"
#include "..\Renderer\DrawingWidgetInterface.h"
#include "..\Renderer\DrawingWidgetInterfaceManager.h"

ProgressBarWidget::ProgressBarWidget() :
	Progress(0.0f),
	Color(FColor::White())
{
}

void ProgressBarWidget::Render()
{
	UpdateWorldPosition();
	DrawingWidgetInterfaceManager::GetInstance().GetWidgetDrawingInterface()->RenderProgressBar(*this);
}