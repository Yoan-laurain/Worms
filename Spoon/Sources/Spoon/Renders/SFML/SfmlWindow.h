#pragma once
#include "snpch.h"
#include "Core/Window.h"
#include "Library/TVector.h"
#include "..\..\Widgets\Renderer\DrawingWidgetInterfaceManager.h"
#include "Widgets/Renderer/DrawingWidgetInterface.h"
#include <SFML/Graphics.hpp>

namespace sf { class Shape; };

class SShapeComponent;

class SPOON_API SfmlWindow : public Window
{

	std::mutex _mutex;

public:
	SfmlWindow(const WindowsProps& props);
	virtual ~SfmlWindow() override;

	void OnUpdate() override;

	void OnRender() override;

	virtual void Draw(const class SActor* _currentActor);

#if DEBUG
	void DrawDebugPoint(const FTransform& transforme);
	void DrawAllDebugs(std::vector<DebugShapeData>& DebugShapes) override;
#endif

	inline void SetEventCallback(const EventCallBackFn& callback) override { EventCallBack = callback;};

	inline void SetEventRenderBack(const std::function<void()>& callback) override { EventRenderBack = callback; }
	
	unsigned int GetWidth() const override;
	unsigned int GetHeight() const override;
	void SetTexture(const SShapeComponent* _component, sf::Shape& _shape);

	void DrawCircle(class SCircleComponent* _component, sf::CircleShape& _circle);
	void DrawConvex(const class SPolygonComponent* _component, sf::ConvexShape& _convex);
	
#if DEBUG
	void SetCollidingState(sf::Shape& _shape, const SActor* _actor);
#endif
	
	void SetCommonShapeProperties(sf::Shape& _shape, const class SShapeComponent* _actor);
	void RenderDrawable(const sf::Drawable& _drawable);

	void SetWidgetDrawingInterface(const char* _interfaceName);
	sf::Sprite& GetSprite(const ImageWidget& image);

	void HandleCursorState();

public:
	bool bIsHoveringSomething;

private:
	
	// Todo voir comment faire des petits class pour juste garder la logique des graph
	std::vector<FVector2D> Graph;
	std::vector<FVector2D> TickGraph;

	bool m_bFrameLimitActivated = true;
	
	sf::Clock m_ClockLogic;

	sf::Clock m_ClockDraw;

	sf::Clock m_GlobalClock;

	sf::Time m_TimeLogic;

	float m_DrawTime;

	sf::RenderWindow* WindowRef;
	
	virtual void Init(const WindowsProps& props);

	virtual void Shutdown();
	struct Data
	{
		std::string Title = "";
		unsigned int Width = 0;
		unsigned int Height = 0;
	};

	Data m_Data;

	void HandleEvent(sf::Event& event);

	void DrawImGuiWin();
	void HandleSelectedWidgetInterfaceChanged();
	void OnWidgetInterfaceSet(const char* key, const std::shared_ptr<DrawingWidgetInterface>& value); 

	// Function to callback
	EventCallBackFn EventCallBack;

	std::function<void()> EventRenderBack;

	char* WidgetInterfaceSelectedIndex;
	char* WidgetInterfaceSelectedPreviousIndex;
	
	std::map<const char*, std::shared_ptr<DrawingWidgetInterface>> WidgetDrawingInterfaces;
};