#pragma once

#include "..\DrawingWidgetInterface.h"
#include "Core/Core.h"

struct Style;

class SPOON_API ImGuiWidgetRenderer : public DrawingWidgetInterface
{
	public:
		ImGuiWidgetRenderer() = default;
		~ImGuiWidgetRenderer() override = default;

		void RenderImage(const ImageWidget& Image) override;
		void RenderText(const TextBlockWidget& TextBlock) override;
		void RenderProgressBar(const ProgressBarWidget& ProgressBar) override;
		void RenderButton(const ButtonWidget& Button) override;

		int PushStyleColor(const Style& Style);
		int PushStyleVar(const Style& Style);
};
