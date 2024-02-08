#pragma once

#include "../Widget.h"
#include "Widgets/TextBlock/TextBlockWidget.h" // On peut pas forward

class SPOON_API ButtonWidget : public Widget
{
	public:
		ButtonWidget();
		virtual ~ButtonWidget() = default;

		virtual void render(Window* window) override;
		virtual void OnClick();

		void SetText(const std::string& text);
		void SetOnClick(std::function<void()> onClick);

	private:
		std::unique_ptr<TextBlockWidget> textBlock;
		std::function<void()> onClick;
};