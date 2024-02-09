#pragma once

#include "../Widget.h"
#include "Library/TColor.h"
#include <string>

class SPOON_API TextBlockWidget : public Widget
{
	public:
		TextBlockWidget();
		~TextBlockWidget() override = default;

		void render() override;
	
		float fontSize;
		std::string text;
		FColor color;
};