#pragma once

#include "../Widget.h"
#include <string>

struct FColor;

class SPOON_API TextBlockWidget : public Widget
{
	public:
		TextBlockWidget();
		virtual ~TextBlockWidget() override = default;

		void Render() override;
	
		float FontSize;
		std::string Text;
		FColor color;
};