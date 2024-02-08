#include "ImGuiRenderer.h"
#include "Library/TColor.h"
#include <imgui.h>

ImGuiRenderer::ImGuiRenderer() 
{
}

ImGuiRenderer::~ImGuiRenderer()
{
}

void ImGuiRenderer::RenderImage( Window* window,const std::string& imagePath, const FVector2D& position, const FVector2D& size)
{
	//ImGui::Image
}

void ImGuiRenderer::RenderText( Window* window,const std::string& text, const FVector2D& position, const float fontSize, const FColor& color)
{
	 
}

void ImGuiRenderer::RenderProgressBar( Window* window,const FVector2D& position, const FVector2D& size, const float percentage, const FColor& color, const FColor& backgroundColor)
{
}

void ImGuiRenderer::RenderButton( Window* window,const FVector2D& position, const FVector2D& size)
{
}
