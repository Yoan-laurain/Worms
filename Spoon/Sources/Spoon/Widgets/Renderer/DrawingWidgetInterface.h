#pragma once

#include <Library/TVector.h>

class ImageWidget;
class TextBlockWidget;
class ProgressBarWidget;
class ButtonWidget;

class DrawingWidgetInterface
{
	public :
		virtual ~DrawingWidgetInterface() = default;

		virtual void RenderImage(const ImageWidget& image) = 0;
		virtual void RenderText(const TextBlockWidget& textBlock) = 0;
		virtual void RenderProgressBar(const ProgressBarWidget& progressBar) = 0;
		virtual void RenderButton(const ButtonWidget& button) = 0;
};