#pragma once

#include "../Widget.h"

class ButtonWidget : public Widget
{
	public:
		ButtonWidget();
		virtual ~ButtonWidget() = default;

		virtual void render() override;
		virtual void OnClick() = 0;

		void SetText(const std::string& text);

	private:
		std::string text;
};