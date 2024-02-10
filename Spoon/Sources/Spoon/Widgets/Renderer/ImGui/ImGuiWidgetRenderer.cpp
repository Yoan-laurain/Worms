#include "ImGuiWidgetRenderer.h"
#include "Library/TColor.h"
#include "Renders/SFML/SfmlWindow.h"
#include <imgui.h>

void ImGuiWidgetRenderer::RenderImage(const std::string& imagePath, const FVector2D& position, const FVector2D& size)
{
	// TODO : Handle texture rendering with ImGui

	ImGui::SetCursorPos(ImVec2(position.X, position.Y));
	ImGui::Image( ImTextureID( imagePath.c_str() ), ImVec2(size.X, size.Y));	 
}

void ImGuiWidgetRenderer::RenderText( const std::string& text, const FVector2D& position, const float fontSize, const FColor& color)
{
	// TODO: Handle font size

    ImGui::SetCursorPos(ImVec2(position.X, position.Y));

    ImGui::TextColored(ImVec4(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f), text.c_str());
}

void ImGuiWidgetRenderer::RenderProgressBar(const FVector2D& position, const FVector2D& size, const float percentage, const FColor& color, const FColor& backgroundColor)
{
	ImGui::SetCursorPos(ImVec2(position.X, position.Y));
	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f));
	ImGui::ProgressBar(percentage, ImVec2(size.X, size.Y), "");
	ImGui::PopStyleColor();
}

void ImGuiWidgetRenderer::RenderButton(const FVector2D& position, const FVector2D& size, const std::string& text, const FColor& color)
{
	// TODO : Handle button color

	ImGui::SetCursorPos(ImVec2(position.X, position.Y));

	const char* textChar = text.c_str();

	ImGui::Button(textChar, ImVec2(size.X, size.Y));
}