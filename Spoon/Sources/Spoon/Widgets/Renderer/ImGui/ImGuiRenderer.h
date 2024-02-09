#pragma once

#include "../DrawingInterface.h"

class ImGuiRenderer : public DrawingInterface
{
	public:
		ImGuiRenderer();
		~ImGuiRenderer() override;

		void RenderImage( Window* window,const std::string& imagePath, const FVector2D& position, const FVector2D& size) override;
		void RenderText( Window* window,const std::string& text, const FVector2D& position, const float fontSize, const FColor& color) override;
		void RenderProgressBar( Window* window,const FVector2D& position, const FVector2D& size, const float percentage, const FColor& color, const FColor& backgroundColor) override;
		void RenderButton( Window* window,const FVector2D& position, const FVector2D& size, const std::string& text ,const FColor& color) override;
};