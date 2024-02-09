#pragma once

#include <Library/TVector.h>
#include <Library/TColor.h>

class Window;

class DrawingInterface
{
	public :
		virtual ~DrawingInterface() = default;

		virtual void RenderImage( Window* window,const std::string& imagePath, const FVector2D& position, const FVector2D& size) = 0;
		virtual void RenderText( Window* window,const std::string& text, const FVector2D& position, const float fontSize, const FColor& color) = 0;
		virtual void RenderProgressBar( Window* window,const FVector2D& position, const FVector2D& size, const float percentage, const FColor& color, const FColor& backgroundColor) = 0;
		virtual void RenderButton( Window* window,const FVector2D& position, const FVector2D& size, const std::string& text, const FColor& color) = 0;
};