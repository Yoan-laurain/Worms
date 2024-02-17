#pragma once

#include "..\DrawingWidgetInterface.h"
#include "Core/Core.h"

struct Style;

class SPOON_API ImGuiWidgetRenderer : public DrawingWidgetInterface
{
	public:
		ImGuiWidgetRenderer() = default;
		~ImGuiWidgetRenderer() override = default;

		void RenderImage(const ImageWidget& image) override;
		void RenderText(const TextBlockWidget& textBlock) override;
		void RenderProgressBar(const ProgressBarWidget& progressBar) override;
		void RenderButton(const ButtonWidget& button) override;

		int PushStyleColor(const Style& style);
		int PushStyleVar(const Style& style);
};
