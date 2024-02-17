#pragma once

#include "..\DrawingWidgetInterface.h"
#include "Core/Core.h"

class SPOON_API SFMLWidgetRenderer : public DrawingWidgetInterface
{
	public:
		SFMLWidgetRenderer() = default;
		~SFMLWidgetRenderer() override = default;
	
		void RenderImage(const ImageWidget& image) override;
		void RenderText(const TextBlockWidget& textBlock) override;
		void RenderProgressBar(const ProgressBarWidget& progressBar) override;
		void RenderButton(const ButtonWidget& button) override;
};