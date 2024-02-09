#pragma once

#include <Library/TVector.h>

class DrawingWidgetInterface
{
	public :
		virtual ~DrawingWidgetInterface() = default;

		virtual void RenderImage(const std::string& imagePath, const FVector2D& position, const FVector2D& size) = 0;
		virtual void RenderText(const std::string& text, const FVector2D& position, const float fontSize, const FColor& color) = 0;
		virtual void RenderProgressBar(const FVector2D& position, const FVector2D& size, const float percentage, const FColor& color, const FColor& backgroundColor) = 0;
		virtual void RenderButton(const FVector2D& position, const FVector2D& size, const std::string& text, const FColor& color) = 0;
};