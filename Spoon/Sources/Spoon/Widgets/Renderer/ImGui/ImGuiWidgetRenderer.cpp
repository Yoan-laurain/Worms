#include "ImGuiWidgetRenderer.h"
#include "Library/TColor.h"
#include "Renders/SFML/SfmlWindow.h"
#include "Widgets/Image/ImageWidget.h"
#include "Widgets/TextBlock/TextBlockWidget.h"
#include "Widgets/ProgressBar/ProgressBarWidget.h"
#include "Widgets/Button/ButtonWidget.h"
#include <imgui.h>

void ImGuiWidgetRenderer::RenderImage(const ImageWidget& image)
{
	// TODO : Handle texture rendering with ImGui

	ImGui::SetCursorPos(ImVec2(image.worldPosition.X, image.worldPosition.Y));
	ImGui::Image( ImTextureID(image.ImagePath.c_str() ), ImVec2(image.Size.X, image.Size.Y));
}

void ImGuiWidgetRenderer::RenderText(const TextBlockWidget& textBlock)
{
	// TODO: Handle font size

    ImGui::SetCursorPos(ImVec2(textBlock.worldPosition.X, textBlock.worldPosition.Y));

    ImGui::TextColored(ImVec4(textBlock.color.R / 255.0f, textBlock.color.G / 255.0f,
		textBlock.color.B / 255.0f, textBlock.color.A / 255.0f), textBlock.Text.c_str());
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
	// TODO : Handle button color

	ImGui::SetCursorPos(ImVec2(button.worldPosition.X, button.worldPosition.Y));

	if (button.GetImage())
	{
		ImGui::ImageButton(ImTextureID(button.GetImage()->ImagePath.c_str()), ImVec2(button.Size.X, button.Size.Y));
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
}