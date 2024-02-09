#include "ImGuiRenderer.h"
#include "Library/TColor.h"
#include "Spoon/Renders/SFML/TextureMgr.h"
#include <imgui.h>
#include <imgui-SFML.h>
#include <Renders/SFML/SfmlWindow.h>
#include <Spoon.h>

ImGuiRenderer::ImGuiRenderer() 
{
}

ImGuiRenderer::~ImGuiRenderer()
{
}

void ImGuiRenderer::RenderImage( Window* window,const std::string& imagePath, const FVector2D& position, const FVector2D& size)
{
	// TODO : Handle texture rendering with ImGui

	ImGui::SetCursorPos(ImVec2(position.X, position.Y));
	ImGui::Image( ImTextureID( imagePath.c_str() ), ImVec2(size.X, size.Y));	 
}

void ImGuiRenderer::RenderText(Window* window, const std::string& text, const FVector2D& position, const float fontSize, const FColor& color)
{
	// TODO: Handle font size

    ImGui::SetCursorPos(ImVec2(position.X, position.Y));

    ImGui::TextColored(ImVec4(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f), text.c_str());
}

void ImGuiRenderer::RenderProgressBar( Window* window,const FVector2D& position, const FVector2D& size, const float percentage, const FColor& color, const FColor& backgroundColor)
{
	ImGui::SetCursorPos(ImVec2(position.X, position.Y));
	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f));
	ImGui::ProgressBar(percentage, ImVec2(size.X, size.Y), "");
	ImGui::PopStyleColor();
}

void ImGuiRenderer::RenderButton( Window* window,const FVector2D& position, const FVector2D& size, const std::string& text, const FColor& color)
{
	// TODO : Handle button color

	ImGui::SetCursorPos(ImVec2(position.X, position.Y));

	const char* textChar = text.c_str();

	ImGui::Button(textChar, ImVec2(size.X, size.Y));
}