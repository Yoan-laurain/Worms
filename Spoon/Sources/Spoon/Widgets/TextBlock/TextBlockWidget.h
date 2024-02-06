#pragma once

#include "../Widget.h"
#include <string>

class TextBlockWidget : public Widget
{
	public:
		TextBlockWidget();
		virtual ~TextBlockWidget() = default;

		void render() override;
		void setText(const std::string& text);

private:
	std::string text;
};