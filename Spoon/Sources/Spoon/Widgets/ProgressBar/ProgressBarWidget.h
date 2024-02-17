#pragma once

#include "../Widget.h"

struct FColor;

class SPOON_API ProgressBarWidget : public Widget
{
	public:
		ProgressBarWidget();
		virtual ~ProgressBarWidget() override = default;

		void Render() override;
	
		float Progress;
		FColor Color;
};