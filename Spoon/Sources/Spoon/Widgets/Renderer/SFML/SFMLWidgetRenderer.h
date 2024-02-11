#pragma once

#include "..\DrawingWidgetInterface.h"

class SPOON_API SFMLWidgetRenderer : public DrawingWidgetInterface
{
	public:
		void RenderImage(const ImageWidget& image) override;
		void RenderText(const TextBlockWidget& textBlock) override;
		void RenderProgressBar(const ProgressBarWidget& progressBar) override;
		void RenderButton(const ButtonWidget& button) override;
};