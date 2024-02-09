#include "ImGuiRenderer.h"
#include "Library/TColor.h"
#include <imgui.h>
#include <imgui-SFML.h>
#include <Renders/SFML/SfmlWindow.h>

ImGuiRenderer::ImGuiRenderer() 
{
}

ImGuiRenderer::~ImGuiRenderer()
{
}

void ImGuiRenderer::RenderImage( Window* window,const std::string& imagePath, const FVector2D& position, const FVector2D& size)
{
	ImGui::SetCursorPos(ImVec2(position.X, position.Y));
	ImGui::Image( ImTextureID( imagePath.c_str() ), ImVec2(size.X, size.Y));	 
}

void ImGuiRenderer::RenderText( Window* window,const std::string& text, const FVector2D& position, const float fontSize, const FColor& color)
{
	ImGui::SetCursorPos(ImVec2(position.X, position.Y));
	ImGui::TextColored(ImVec4(color.R, color.G, color.B, color.A), text.c_str());
}

void ImGuiRenderer::RenderProgressBar( Window* window,const FVector2D& position, const FVector2D& size, const float percentage, const FColor& color, const FColor& backgroundColor)
{
	ImGui::SetCursorPos(ImVec2(position.X, position.Y));
	ImGui::ProgressBar(percentage, ImVec2(size.X, size.Y));
}

void ImGuiRenderer::RenderButton( Window* window,const FVector2D& position, const FVector2D& size, const std::string& text)
{
	ImGui::SetCursorPos(ImVec2(position.X, position.Y));

	const char* textChar = text.c_str();
	ImGui::Button(textChar, ImVec2(size.X, size.Y));
}