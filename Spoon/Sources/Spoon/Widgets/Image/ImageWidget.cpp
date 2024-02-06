#include "ImageWidget.h"

ImageWidget::ImageWidget()
{
}

void ImageWidget::render()
{
	if (renderer)
	{
		renderer->RenderImage(imagePath, position, size);
	}
}

void ImageWidget::SetBackgroundImage(std::string imagePath)
{
}