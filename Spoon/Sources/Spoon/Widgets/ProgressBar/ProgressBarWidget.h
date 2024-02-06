#pragma once

#include "../Widget.h"

class ProgressBarWidget : public Widget
{
	public:
		ProgressBarWidget();
		virtual ~ProgressBarWidget() = default;

		void render() override;
		void setProgress(float progress);

	private:
		float progress;
};