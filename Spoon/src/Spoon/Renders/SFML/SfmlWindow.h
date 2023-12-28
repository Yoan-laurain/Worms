#pragma once
#include "snpch.h"
#include "Spoon/Core/Window.h"

#include <SFML/Graphics.hpp>

namespace sf { class Shape; };

class SfmlWindow : public Window
{

	std::mutex _mutex;

public:
	SfmlWindow(const WindowsProps& props);
	virtual ~SfmlWindow() override;

	void OnUpdate() override;

	void OnRender() override;

	virtual void Draw(const class SActor* _currentActor);

	inline void SetEventCallback(const EventCallBackFn& callback) override { EventCallBack = callback;};

	inline void SetEventRenderBack(const std::function<void()>& callback) override { EventRenderBack = callback; }
	
	unsigned int GetWidth() const override;
	unsigned int GetHeight() const override;

	void DrawRectangle(const SActor* _currentActor, sf::RectangleShape& _rectangle);
	void DrawConvex(const SActor* _currentActor, sf::ConvexShape& _convex);
	void DrawTexture(const SActor* _currentActor, sf::Sprite& _text);

private:
	
	sf::Clock clock;

	sf::RenderWindow* WindowRef;

	std::vector<sf::Texture> Textures;
	
	virtual void Init(const WindowsProps& props);

	virtual void Shutdown();
	struct Data
	{
		std::string Title = "";
		unsigned int Width, Height = 0;
	};

	Data m_Data;

	void HandleEvent(sf::Event& event);

#ifndef DEBUG
	void DrawImGuiWin();
#endif // !DEBUG

	// Function to callback
	EventCallBackFn EventCallBack;

	std::function<void()> EventRenderBack;
};

