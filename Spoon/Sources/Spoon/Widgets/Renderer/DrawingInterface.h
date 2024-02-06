#pragma once

#include <Library/TVector.h>

class DrawingInterface
{
	public : 

		virtual ~DrawingInterface() = default;

		virtual void RenderImage(std::string imagePath, FVector2D position, FVector2D size) = 0;
		virtual void RenderText(std::string text, FVector2D position, FVector2D size, float fontSize, std::string fontName, std::string color) = 0;

};