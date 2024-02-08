#pragma once

#include "../Widget.h"
#include "Library/TColor.h"

class SPOON_API ProgressBarWidget : public Widget
{
	public:
		ProgressBarWidget();
		virtual ~ProgressBarWidget() = default;

		void render(Window* window) override;
		void setProgress(float progress);
		void setColor(const FColor& color);
		void setBackgroundColor(const FColor& color);

	private:
		float progress;
		FColor color;
		FColor backgroundColor;
};