#include "ImGuiWidgetRenderer.h"
#include "Library/TColor.h"
#include "Renders/SFML/SfmlWindow.h"
#include "Widgets/Image/ImageWidget.h"
#include "Widgets/TextBlock/TextBlockWidget.h"
#include "Widgets/ProgressBar/ProgressBarWidget.h"
#include "Widgets/Button/ButtonWidget.h"
#include <imgui.h>
#include <imgui-SFML.h>
#include "Core/Application.h"
#include "Widgets/Widget.h"
#include "Renders/SFML/TextureMgr.h"

void ImGuiWidgetRenderer::RenderImage(const ImageWidget& image)
{
	if (image.ImagePath.empty())
	{
		return;
	}
	
	ImGui::SetCursorPos(ImVec2(image.worldPosition.X, image.worldPosition.Y));
	
	SfmlWindow* window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (window)
	{
		sf::Sprite& sprite = window->GetSprite(image);

		// Imgui does not seams to handle image rotation : cf https://github.com/SFML/imgui-sfml/issues/86
		ImGui::Image(sprite, ImVec2(image.Size.X, image.Size.Y));
	}
}

void ImGuiWidgetRenderer::RenderText(const TextBlockWidget& textBlock)
{
	// TODO : Handle font size

    ImGui::SetCursorPos(ImVec2(textBlock.worldPosition.X, textBlock.worldPosition.Y));

	ImGui::SetWindowFontScale(textBlock.FontSize / 10.f); 

    ImGui::TextColored(ImVec4(textBlock.color.R / 255.0f, textBlock.color.G / 255.0f,
		textBlock.color.B / 255.0f, textBlock.color.A / 255.0f), textBlock.Text.c_str());

	ImGui::SetWindowFontScale(1.0f);
}

void ImGuiWidgetRenderer::RenderProgressBar(const ProgressBarWidget& progressBar)
{
	ImGui::SetCursorPos(ImVec2(progressBar.worldPosition.X, progressBar.worldPosition.Y));
	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(progressBar.color.R / 255.0f, progressBar.color.G / 255.0f,
		progressBar.color.B / 255.0f, progressBar.color.A / 255.0f));
	ImGui::ProgressBar(progressBar.progress, ImVec2(progressBar.Size.X, progressBar.Size.Y), "");
	ImGui::PopStyleColor();
}

void ImGuiWidgetRenderer::RenderButton(const ButtonWidget& button)
{
	const Style& StyleToApply = button.GetStyle();

	ImGui::SetCursorPos(ImVec2(button.worldPosition.X, button.worldPosition.Y));

	int StylePushedCount = PushStyleColor(StyleToApply);
	int StyleVarPushedCount = PushStyleVar(StyleToApply);

	if (button.GetImage())
	{
		SfmlWindow* window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

		if (window)
		{
			ImGui::ImageButton(
				window->GetSprite(*button.GetImage())
				, ImVec2(button.Size.X, button.Size.Y)
				,0
				, sf::Color::Transparent
				);
		}
	}
	else
	{
		const char* textChar = "##";

		if (button.GetTextBlock())
		{
			textChar = button.GetTextBlock()->Text.c_str();
		}

		ImGui::Button(textChar, ImVec2(button.Size.X, button.Size.Y));
	}

	ImGui::PopStyleColor(StylePushedCount);
	ImGui::PopStyleVar(StyleVarPushedCount);
}

int ImGuiWidgetRenderer::PushStyleVar(const Style& style)
{
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, style.OutlineThickness);
	return 1;
}

int ImGuiWidgetRenderer::PushStyleColor(const Style& style)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(style.Color.R / 255.0f, style.Color.G / 255.0f, style.Color.B / 255.0f, style.Color.A / 255.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(style.Color.R / 255.0f, style.Color.G / 255.0f, style.Color.B / 255.0f, style.Color.A / 255.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(style.Color.R / 255.0f, style.Color.G / 255.0f, style.Color.B / 255.0f, style.Color.A / 255.0f));


	ImGui::PushStyleColor(ImGuiCol_Border,
		ImVec4( 
			style.OutlineColor.R / 255.0f,
			style.OutlineColor.G / 255.0f,
			style.OutlineColor.B / 255.0f,
			style.OutlineColor.A / 255.0f
		));

	return 4;
}
