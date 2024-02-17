#pragma once

#include "../Widget.h"
#include "Widgets/TextBlock/TextBlockWidget.h" 
#include "Widgets/Image/ImageWidget.h"

class SPOON_API ButtonWidget : public Widget
{
	public:
		ButtonWidget();
		~ButtonWidget() override = default;

		void Render() override;
		virtual void CallOnClick();

		void SetText(const std::string& Text);
		void SetBackgroundImage(const std::string& ImagePath);
		void SetIsEnabled(bool bIsEnabled) override;

		ImageWidget* GetImage() const;
		TextBlockWidget* GetTextBlock() const;

		Style& GetStyle() const override;

		Style SelectedStyle;

		std::function<void()> OnClick; 

		bool bIsSelected;

private:
		 		
		std::unique_ptr<TextBlockWidget> TextBlock;
		std::unique_ptr<ImageWidget> Image;
};