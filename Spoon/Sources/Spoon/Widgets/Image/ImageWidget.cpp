#include "ImageWidget.h"
#include "../Renderer/DrawingInterface.h"
#include "Core/Window.h"
#include <Widgets/Renderer/DrawingInterfaceManager.h>

ImageWidget::ImageWidget()
{
}

void ImageWidget::render(Window* window)
{
	UpdateWorldPosition();
	DrawingInterfaceManager::getInstance().getDrawingInterface()->RenderImage(window, imagePath, worldPosition, size);
}

void ImageWidget::SetBackgroundImage(std::string imagePath)
{
	this->imagePath = imagePath;
}