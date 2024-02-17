#include "ImGuiWidgetRenderer.h"
#include "Library/TColor.h"
#include "Renders/SFML/SfmlWindow.h"
#include "Widgets/Image/ImageWidget.h"
#include "Widgets/TextBlock/TextBlockWidget.h"
#include "Widgets/ProgressBar/ProgressBarWidget.h"
#include "Widgets/Button/ButtonWidget.h"
#include "Core/Application.h"
#include "Widgets/Widget.h"
#include "Renders/SFML/TextureMgr.h"
#include <imgui.h>
#include <imgui-SFML.h>

void ImGuiWidgetRenderer::RenderImage(const ImageWidget& Image)
{
	if (Image.ImagePath.empty())
	{
		return;
	}
	
	ImGui::SetCursorPos(ImVec2(Image.WorldPosition.X, Image.WorldPosition.Y));
	
	SfmlWindow* Window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (Window)
	{
		sf::Sprite& Sprite = Window->GetSprite(Image);

		// Imgui does not seams to handle image rotation : cf https://github.com/SFML/imgui-sfml/issues/86
		ImGui::Image(Sprite, ImVec2(Image.Size.X, Image.Size.Y));
	}
}

void ImGuiWidgetRenderer::RenderText(const TextBlockWidget& TextBlock)
{
	// TODO : Handle font size

    ImGui::SetCursorPos(ImVec2(TextBlock.WorldPosition.X, TextBlock.WorldPosition.Y));

	ImGui::SetWindowFontScale(TextBlock.FontSize / 10.f); 

    ImGui::TextColored(ImVec4(TextBlock.color.R / 255.0f, TextBlock.color.G / 255.0f,
		TextBlock.color.B / 255.0f, TextBlock.color.A / 255.0f), TextBlock.Text.c_str());

	ImGui::SetWindowFontScale(1.0f);
}

void ImGuiWidgetRenderer::RenderProgressBar(const ProgressBarWidget& ProgressBar)
{
	ImGui::SetCursorPos(ImVec2(ProgressBar.WorldPosition.X, ProgressBar.WorldPosition.Y));
	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(ProgressBar.Color.R / 255.0f, ProgressBar.Color.G / 255.0f,
		ProgressBar.Color.B / 255.0f, ProgressBar.Color.A / 255.0f));
	ImGui::ProgressBar(ProgressBar.Progress, ImVec2(ProgressBar.Size.X, ProgressBar.Size.Y), "");
	ImGui::PopStyleColor();
}

void ImGuiWidgetRenderer::RenderButton(const ButtonWidget& Button)
{
	const Style& StyleToApply = Button.GetStyle();

	ImGui::SetCursorPos(ImVec2(Button.WorldPosition.X, Button.WorldPosition.Y));

	int StylePushedCount = PushStyleColor(StyleToApply);
	int StyleVarPushedCount = PushStyleVar(StyleToApply);

	if (Button.GetImage())
	{
		SfmlWindow* Window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

		if (Window)
		{
			ImGui::ImageButton(
				Window->GetSprite(*Button.GetImage())
				, ImVec2(Button.Size.X, Button.Size.Y)
				,0
				, sf::Color::Transparent
				);
		}
	}
	else
	{
		const char* TextChar = "##";

		if (Button.GetTextBlock())
		{
			TextChar = Button.GetTextBlock()->Text.c_str();
		}

		ImGui::Button(TextChar, ImVec2(Button.Size.X, Button.Size.Y));
	}

	ImGui::PopStyleColor(StylePushedCount);
	ImGui::PopStyleVar(StyleVarPushedCount);
}

int ImGuiWidgetRenderer::PushStyleVar(const Style& Style)
{
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, Style.OutlineThickness);
	return 1;
}

int ImGuiWidgetRenderer::PushStyleColor(const Style& Style)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(Style.Color.R / 255.0f, Style.Color.G / 255.0f, Style.Color.B / 255.0f, Style.Color.A / 255.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(Style.Color.R / 255.0f, Style.Color.G / 255.0f, Style.Color.B / 255.0f, Style.Color.A / 255.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(Style.Color.R / 255.0f, Style.Color.G / 255.0f, Style.Color.B / 255.0f, Style.Color.A / 255.0f));


	ImGui::PushStyleColor(ImGuiCol_Border,
		ImVec4( 
			Style.OutlineColor.R / 255.0f,
			Style.OutlineColor.G / 255.0f,
			Style.OutlineColor.B / 255.0f,
			Style.OutlineColor.A / 255.0f
		));

	return 4;
}
