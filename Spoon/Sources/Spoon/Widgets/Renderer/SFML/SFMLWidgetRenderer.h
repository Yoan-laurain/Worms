#pragma once

#include "..\DrawingWidgetInterface.h"
#include "Core/Core.h"

class SPOON_API SFMLWidgetRenderer : public DrawingWidgetInterface
{
	public:
		SFMLWidgetRenderer() = default;
		~SFMLWidgetRenderer() override = default;
	
		void RenderImage(const ImageWidget& Image) override;
		void RenderText(const TextBlockWidget& TextBlock) override;
		void RenderProgressBar(const ProgressBarWidget& ProgressBar) override;
		void RenderButton(const ButtonWidget& Button) override;
};