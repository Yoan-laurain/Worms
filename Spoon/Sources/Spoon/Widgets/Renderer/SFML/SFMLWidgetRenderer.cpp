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
#include "Library/MathLibrary.h"
#include <SFML/Graphics.hpp>

void SFMLWidgetRenderer::RenderImage(const ImageWidget& image)
{
	if (image.ImagePath.empty())
	{
		return;
	}

	sf::Sprite sprite;
	sf::Texture texture;

	if (!Application::Get().GetTextureMgr()->IsTextureLoaded(image.ImagePath))
	{
		Application::Get().GetTextureMgr()->LoadTexture(image.ImagePath, image.ImagePath);
	}
	
	texture = Application::Get().GetTextureMgr()->GetTexture(image.ImagePath);

	sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	sprite.setPosition(image.worldPosition.X + image.Size.X / 2.f, image.worldPosition.Y + image.Size.Y / 2.f);
	sprite.setScale(image.Size.X / texture.getSize().x, image.Size.Y / texture.getSize().y);
	sprite.setTexture(texture);
	sprite.setRotation(image.Rotation);

	SfmlWindow* window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (window)
	{
		window->RenderDrawable(sprite);
	}
}

void SFMLWidgetRenderer::RenderText(const TextBlockWidget& textBlock)
{
	sf::Text sfText;
	sf::Font font;

	if (!Application::Get().GetTextureMgr()->IsFontLoaded("Roboto-Black"))
	{
		Application::Get().GetTextureMgr()->LoadFont("Roboto-Black", "Ressources/Roboto-Black.ttf");
	}

	font = Application::Get().GetTextureMgr()->GetFont("Roboto-Black");

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

void SFMLWidgetRenderer::RenderProgressBar(const ProgressBarWidget& progressBar)
{
	sf::RectangleShape background; 
	background.setSize(sf::Vector2f(progressBar.Size.X, progressBar.Size.Y));
	background.setFillColor(sf::Color(progressBar.BackgroundColor.R, progressBar.BackgroundColor.G, progressBar.BackgroundColor.B, progressBar.BackgroundColor.A));
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
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(button.Size.X, button.Size.Y));

	float alpha = MathLibrary::Clamp(button.BackgroundColor.A / 255.f, 0.f, 1.f);

	rectangle.setOutlineThickness(2.f);

	if (!button.IsEnabled())
	{
		alpha = 0.2f;
		rectangle.setOutlineColor(sf::Color::Red);
	}
	else
	{
		rectangle.setOutlineColor(sf::Color::White);
	}
	 
	if (button.IsHovered() || button.bIsSelected) 
	{
		alpha = 1.f;
	}

	sf::Color sfmlColor = sf::Color( button.BackgroundColor.R, button.BackgroundColor.G, button.BackgroundColor.B, alpha * 255.f);
	rectangle.setFillColor(sfmlColor); 

	rectangle.setPosition(button.worldPosition.X, button.worldPosition.Y);

	SfmlWindow* window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (window)
	{
		window->RenderDrawable(rectangle);
	}
}