#pragma once

#include "../Widget.h"
#include "Widgets/TextBlock/TextBlockWidget.h" // On peut pas forward
#include "Widgets/Image/ImageWidget.h" // On peut pas forward

class SPOON_API ButtonWidget : public Widget
{
	public:
		ButtonWidget();
		~ButtonWidget() override = default;

		void Render() override;
		virtual void CallOnClick();

		void SetText(const std::string& text);
		void SetBackgroundImage(const std::string& imagePath);
		void SetIsEnabled(bool bIsEnabled) override;

		ImageWidget* GetImage() const;
		TextBlockWidget* GetTextBlock() const;

		std::function<void()> OnClick; 

		bool bIsSelected;

private:
		 		
		std::unique_ptr<TextBlockWidget> textBlock;
		std::unique_ptr<ImageWidget> image;
};