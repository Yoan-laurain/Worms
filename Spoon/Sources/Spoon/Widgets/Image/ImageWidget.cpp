#include "ImageWidget.h"
#include "../Renderer/DrawingInterface.h"
#include "Core/Window.h"

ImageWidget::ImageWidget()
{
}

void ImageWidget::render(Window* window)
{
	if ( !renderer.expired() )
	{
		UpdateWorldPosition();
		renderer.lock()->RenderImage(window,imagePath,worldPosition, size);
	}
}

void ImageWidget::SetBackgroundImage(std::string imagePath)
{
	this->imagePath = imagePath;
}