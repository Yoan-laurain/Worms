#pragma once

#include "../Widget.h"
#include "Library/TColor.h"

class SPOON_API ProgressBarWidget : public Widget
{
	public:
		ProgressBarWidget();
		~ProgressBarWidget() override = default;

		void render(Window* window) override;
	
		float progress;
		FColor color;
};