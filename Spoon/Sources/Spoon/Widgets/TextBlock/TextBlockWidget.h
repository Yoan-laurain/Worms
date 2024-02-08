#pragma once

#include "../Widget.h"
#include "Library/TColor.h"
#include <string>

class SPOON_API TextBlockWidget : public Widget
{
	public:
		TextBlockWidget();
		virtual ~TextBlockWidget() = default;

		void render(Window* window) override;

		void setText(const std::string& text);
		void setColor(const FColor color);
		void setFontSize(float fontSize);

		float fontSize;
		std::string text;
private:
	FColor color;

};