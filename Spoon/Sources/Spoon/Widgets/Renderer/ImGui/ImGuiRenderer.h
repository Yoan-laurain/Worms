#pragma once

#include "../DrawingInterface.h"

class ImGuiRenderer : public DrawingInterface
{
	public:
		ImGuiRenderer();
		virtual ~ImGuiRenderer() override;

		virtual void RenderImage(std::string imagePath, FVector2D position, FVector2D size);
};