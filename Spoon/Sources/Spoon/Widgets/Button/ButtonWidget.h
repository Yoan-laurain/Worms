#pragma once

#include "../Widget.h"
#include "Widgets/TextBlock/TextBlockWidget.h" // On peut pas forward

class SPOON_API ButtonWidget : public Widget
{
	public:
		ButtonWidget();
		~ButtonWidget() override = default;

		void render(Window* window) override;
		virtual void OnClick();

		void SetText(const std::string& text);
		std::function<void()> onClick;

	private:
		std::unique_ptr<TextBlockWidget> textBlock;
};