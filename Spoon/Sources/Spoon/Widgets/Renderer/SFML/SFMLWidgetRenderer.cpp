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

void SFMLWidgetRenderer::RenderImage(const ImageWidget& Image)
{
	if (Image.ImagePath.empty())
	{
		return;
	}
	
	SfmlWindow* Window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (Window)
	{
		sf::Sprite& sprite = Window->GetSprite(Image);
		Window->RenderDrawable(sprite);
	}
}

void SFMLWidgetRenderer::RenderText(const TextBlockWidget& TextBlock)
{
	sf::Text SfText;

	if (!Application::Get().GetTextureMgr()->IsFontLoaded("Roboto-Black"))
	{
		Application::Get().GetTextureMgr()->LoadFont("Roboto-Black", "Ressources/Roboto-Black.ttf");
	}

	sf::Font& Font = Application::Get().GetTextureMgr()->GetFont("Roboto-Black");

	SfText.setFont(Font);
	SfText.setString(TextBlock.Text);
	SfText.setCharacterSize(TextBlock.FontSize);
	SfText.setFillColor(sf::Color(TextBlock.color.R, TextBlock.color.G, TextBlock.color.B, TextBlock.color.A));
	SfText.setPosition(TextBlock.WorldPosition.X, TextBlock.WorldPosition.Y);

	SfmlWindow* Window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (Window)
	{
		Window->RenderDrawable( SfText );
	}
}

void SFMLWidgetRenderer::RenderProgressBar(const ProgressBarWidget& ProgressBar )
{
	Style& StyleToApply = ProgressBar.GetStyle();
	
	sf::RectangleShape Background; 
	Background.setSize(sf::Vector2f(ProgressBar.Size.X, ProgressBar.Size.Y));
	Background.setFillColor(sf::Color(StyleToApply.Color.R, StyleToApply.Color.G, StyleToApply.Color.B, StyleToApply.Color.A));
	Background.setPosition(ProgressBar.WorldPosition.X, ProgressBar.WorldPosition.Y);

	sf::RectangleShape Rectangle;
	Rectangle.setSize(sf::Vector2f(ProgressBar.Size.X * ProgressBar.Progress, ProgressBar.Size.Y));
	Rectangle.setFillColor(sf::Color(ProgressBar.Color.R, ProgressBar.Color.G, ProgressBar.Color.B, ProgressBar.Color.A));
	Rectangle.setPosition(ProgressBar.WorldPosition.X, ProgressBar.WorldPosition.Y);

	SfmlWindow* Window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (Window)
	{
		Window->RenderDrawable( Background );
		Window->RenderDrawable( Rectangle );
	}
}

void SFMLWidgetRenderer::RenderButton(const ButtonWidget& Button)
{
	const Style& StyleToApply = Button.GetStyle();
	
	sf::RectangleShape Rectangle;
	
	Rectangle.setSize(sf::Vector2f(Button.Size.X, Button.Size.Y));

	Rectangle.setOutlineThickness( StyleToApply.OutlineThickness );
	Rectangle.setOutlineColor( sf::Color( StyleToApply.OutlineColor.R, StyleToApply.OutlineColor.G, StyleToApply.OutlineColor.B, StyleToApply.OutlineColor.A) );
	
	sf::Color SfmlColor = sf::Color( StyleToApply.Color.R, StyleToApply.Color.G, StyleToApply.Color.B, StyleToApply.Color.A);
	Rectangle.setFillColor(SfmlColor); 

	Rectangle.setPosition(Button.WorldPosition.X, Button.WorldPosition.Y);

	SfmlWindow* Window = dynamic_cast<SfmlWindow*>(Application::Get().GetWindow());

	if (Window)
	{
		Window->RenderDrawable(Rectangle);
	}
}