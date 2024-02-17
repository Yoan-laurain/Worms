#pragma once

class ImageWidget;
class TextBlockWidget;
class ProgressBarWidget;
class ButtonWidget;

class DrawingWidgetInterface
{
	public :
		virtual ~DrawingWidgetInterface() = default;

		virtual void RenderImage(const ImageWidget& Image) = 0;
		virtual void RenderText(const TextBlockWidget& TextBlock) = 0;
		virtual void RenderProgressBar(const ProgressBarWidget& ProgressBar) = 0;
		virtual void RenderButton(const ButtonWidget& Button) = 0;
};