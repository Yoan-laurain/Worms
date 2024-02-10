#include "SFMLWidgetRenderer.h"
#include "Library/TColor.h"
#include "Core/Application.h"
#include "Spoon/Renders/SFML/TextureMgr.h"
#include "Core/Window.h"
#include "Renders/SFML/SfmlWindow.h"
#include <SFML/Graphics.hpp>

void SFMLWidgetRenderer::RenderImage(const std::string& imagePath, const FVector2D& position, const FVector2D& size)
{
	if (imagePath.empty())
	{
		return;
	}

	sf::Sprite sprite;
	sf::Texture texture;

	if (!Application::Get().GetTextureMgr()->IsTextureLoaded(imagePath))
	{
		Application::Get().GetTextureMgr()->LoadTexture(imagePath, imagePath);
	}
	
	texture = Application::Get().GetTextureMgr()->GetTexture(imagePath);

	sprite.setPosition(position.X, position.Y);
	sprite.setScale(size.X / texture.getSize().x, size.Y / texture.getSize().y);
	sprite.setTexture(texture);

	SfmlWindow* window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (window)
	{
		window->RenderDrawable(sprite);
	}
}

void SFMLWidgetRenderer::RenderText(const std::string& text, const FVector2D& position, const float fontSize, const FColor& color)
{
	sf::Text sfText;
	sf::Font font;

	if (!Application::Get().GetTextureMgr()->IsFontLoaded("Roboto-Black"))
	{
		Application::Get().GetTextureMgr()->LoadFont("Roboto-Black", "Ressources/Roboto-Black.ttf");
	}

	font = Application::Get().GetTextureMgr()->GetFont("Roboto-Black");

	sfText.setFont(font);
	sfText.setString(text);
	sfText.setCharacterSize(fontSize); 
	sfText.setFillColor(sf::Color(color.R, color.G, color.B, color.A)); 
	sfText.setPosition(position.X, position.Y); 

	SfmlWindow* window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (window)
	{
		window->RenderDrawable( sfText );
	}
}

void SFMLWidgetRenderer::RenderProgressBar(const FVector2D& position, const FVector2D& size, const float percentage, const FColor& color, const FColor& backgroundColor)
{
	sf::RectangleShape background; 
	background.setSize(sf::Vector2f(size.X, size.Y)); 
	background.setFillColor(sf::Color(backgroundColor.R, backgroundColor.G, backgroundColor.B, backgroundColor.A)); 
	background.setPosition(position.X, position.Y); 

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(size.X * percentage, size.Y));
	rectangle.setFillColor(sf::Color(color.R, color.G, color.B, color.A));
	rectangle.setPosition(position.X, position.Y);

	SfmlWindow* window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (window)
	{
		window->RenderDrawable( background );
		window->RenderDrawable( rectangle );
	}
}

void SFMLWidgetRenderer::RenderButton( const FVector2D& position, const FVector2D& size, const std::string& text, const FColor& color)
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(size.X, size.Y));

	sf::Color sfmlColor = sf::Color(color.R, color.G, color.B, color.A);

	rectangle.setFillColor(sfmlColor);
	rectangle.setPosition(position.X, position.Y);

	SfmlWindow* window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (window)
	{
		window->RenderDrawable( rectangle );
	}
}