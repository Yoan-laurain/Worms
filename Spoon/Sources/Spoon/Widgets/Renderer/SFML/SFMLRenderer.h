#pragma once

#include "../DrawingInterface.h"

class SFMLRenderer : public DrawingInterface
{
	public:
		SFMLRenderer();
		virtual ~SFMLRenderer() override;

		virtual void RenderImage(std::string imagePath, FVector2D position, FVector2D size);


};