#include "SFMLWidgetRenderer.h"
#include "Library/TColor.h"
#include "Core/Application.h"
#include "Spoon/Renders/SFML/TextureMgr.h"
#include "Core/Window.h"
#include "Renders/SFML/SfmlWindow.h"
#include "Widgets/Image/ImageWidget.h"
#include "Widgets/TextBlock/TextBlockWidget.h"
#include "Widgets/ProgressBar/ProgressBarWidget.h"
#include "Widgets/Button/ButtonWidget.h"
#include "Widgets/Widget.h"
#include <SFML/Graphics.hpp>

void SFMLWidgetRenderer::RenderImage(const ImageWidget& image)
{
	if (image.ImagePath.empty())
	{
		return;
	}
	
	SfmlWindow* window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (window)
	{
		sf::Sprite& sprite = window->GetSprite(image);
		window->RenderDrawable(sprite);
	}
}

void SFMLWidgetRenderer::RenderText(const TextBlockWidget& textBlock)
{
	sf::Text sfText;

	if (!Application::Get().GetTextureMgr()->IsFontLoaded("Roboto-Black"))
	{
		Application::Get().GetTextureMgr()->LoadFont("Roboto-Black", "Ressources/Roboto-Black.ttf");
	}

	sf::Font& font = Application::Get().GetTextureMgr()->GetFont("Roboto-Black");

	sfText.setFont(font);
	sfText.setString(textBlock.Text);
	sfText.setCharacterSize(textBlock.FontSize);
	sfText.setFillColor(sf::Color(textBlock.color.R, textBlock.color.G, textBlock.color.B, textBlock.color.A));
	sfText.setPosition(textBlock.worldPosition.X, textBlock.worldPosition.Y);

	SfmlWindow* window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (window)
	{
		window->RenderDrawable( sfText );
	}
}

void SFMLWidgetRenderer::RenderProgressBar(const ProgressBarWidget& progressBar )
{
	Style StyleToApply = progressBar.GetStyle();
	
	sf::RectangleShape background; 
	background.setSize(sf::Vector2f(progressBar.Size.X, progressBar.Size.Y));
	background.setFillColor(sf::Color(StyleToApply.Color.R, StyleToApply.Color.G, StyleToApply.Color.B, StyleToApply.Color.A));
	background.setPosition(progressBar.worldPosition.X, progressBar.worldPosition.Y);

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(progressBar.Size.X * progressBar.progress, progressBar.Size.Y));
	rectangle.setFillColor(sf::Color(progressBar.color.R, progressBar.color.G, progressBar.color.B, progressBar.color.A));
	rectangle.setPosition(progressBar.worldPosition.X, progressBar.worldPosition.Y);

	SfmlWindow* window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (window)
	{
		window->RenderDrawable( background );
		window->RenderDrawable( rectangle );
	}
}

void SFMLWidgetRenderer::RenderButton(const ButtonWidget& button)
{
	const Style& StyleToApply = button.GetStyle();
	
	sf::RectangleShape rectangle;
	
	rectangle.setSize(sf::Vector2f(button.Size.X, button.Size.Y));

	rectangle.setOutlineThickness( StyleToApply.OutlineThickness );
	rectangle.setOutlineColor( sf::Color( StyleToApply.OutlineColor.R, StyleToApply.OutlineColor.G, StyleToApply.OutlineColor.B, StyleToApply.OutlineColor.A) );
	
	sf::Color sfmlColor = sf::Color( StyleToApply.Color.R, StyleToApply.Color.G, StyleToApply.Color.B, StyleToApply.Color.A);
	rectangle.setFillColor(sfmlColor); 

	rectangle.setPosition(button.worldPosition.X, button.worldPosition.Y);

	SfmlWindow* window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (window)
	{
		window->RenderDrawable(rectangle);
	}
}