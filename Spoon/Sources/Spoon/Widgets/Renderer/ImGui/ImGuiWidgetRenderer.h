#pragma once

#include "..\DrawingWidgetInterface.h"

class SPOON_API ImGuiWidgetRenderer : public DrawingWidgetInterface
{
	public:
		ImGuiWidgetRenderer() = default;
		~ImGuiWidgetRenderer() override = default;

		void RenderImage(const std::string& imagePath, const FVector2D& position, const FVector2D& size) override;
		void RenderText(const std::string& text, const FVector2D& position, const float fontSize, const FColor& color) override;
		void RenderProgressBar(const FVector2D& position, const FVector2D& size, const float percentage, const FColor& color, const FColor& backgroundColor) override;
		void RenderButton(const FVector2D& position, const FVector2D& size, const std::string& text ,const FColor& color) override;
};