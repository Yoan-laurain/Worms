#include "SfmlWindow.h"
#include "Objects/SActor.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Objects/Components/SShapeComponent.h"
#include "TextureMgr.h"

#include <imgui.h>
#include <imgui-SFML.h>
#include <implot.h>

#include "Core/Application.h"

namespace Configuration
{
	int FrameRate = 120;
	bool VerticalSync = false;
}

// Function call de maniere indirect lorsque j'ai besoin de la fenetre.
Window* Window::Create(const WindowsProps& props)
{
	return new SfmlWindow(props);
}

// Creation d'une nouvelle fenetre call init page
SfmlWindow::SfmlWindow(const WindowsProps& props)
{
	Init(props);
}

SfmlWindow::~SfmlWindow()
{
	Shutdown();
}

void SfmlWindow::OnUpdate()
{
	// Tick
	std::unique_lock<std::mutex> _lock(_mutex);
	m_TimeLogic = m_ClockLogic.getElapsedTime();
	m_ClockLogic.restart();
	_lock.unlock();
	AppTickEvent TickEvent(m_TimeLogic.asSeconds());
	EventCallBack(TickEvent);
}

void SfmlWindow::OnRender()
{
	sf::Event event;
	while (WindowRef->pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);
		// Todo maybe this function can be thread so the logic will still be separt with the render?
		HandleEvent(event);
	}
	ImGui::SFML::Update(*WindowRef, m_ClockDraw.getElapsedTime());
	WindowRef->clear();
	DrawImGuiWin();
	EventRenderBack();
	ImGui::SFML::Render(*WindowRef);
	WindowRef->display();
}

void SfmlWindow::Draw(const SActor* _currentActor)
{
	if (_currentActor == nullptr || WindowRef == nullptr)
	{
		return;
	}
	std::vector<SShapeComponent*> CompList;
	if(!_currentActor->GetAllComponentType<SShapeComponent*>(CompList))
		return;

	for (SShapeComponent* comp : CompList)
	{
		if (comp->GetType() == FActorType::ActorType_Polygon)
		{
			sf::ConvexShape drawShape;
			DrawConvex(static_cast<SPolygonComponent*>(comp), drawShape);
			WindowRef->draw(drawShape);
		}
		else if(comp->GetType() == FActorType::ActorType_Circle)
		{
			sf::CircleShape drawShape;
			DrawCircle(static_cast<SCircleComponent*>(comp), drawShape);
			WindowRef->draw(drawShape);
		}

		comp->GetOwner()->bIsColliding = false;
	}
}

unsigned int SfmlWindow::GetWidth() const
{
	return m_Data.Width;
}

unsigned int SfmlWindow::GetHeight() const
{
	return m_Data.Height;
}

void SfmlWindow::DrawCircle(SCircleComponent* _component, sf::CircleShape& _circle)
{
	_circle.setOrigin(_component->Origin.X * _component->Radius * 2, _component->Origin.Y * _component->Radius * 2);
	_circle.setRadius(_component->Radius);

	SetCommonShapeProperties(_circle, _component);
}

void SfmlWindow::DrawConvex(SPolygonComponent* _component, sf::ConvexShape& drawShape)
{
	drawShape.setPointCount(_component->Points.size());	

	FVector2D ownerLocation = _component->GetOwner()->GetLocation();

	for (int i = 0; i < _component->Points.size(); i++)
	{
		drawShape.setPoint(i, sf::Vector2f(ownerLocation.X + _component->Points[i].X, ownerLocation.Y + _component->Points[i].Y));

		// For debug purpose only
		sf::CircleShape point(5);
		point.setOrigin(5, 5);
		point.setPosition(sf::Vector2f(ownerLocation.X + _component->Points[i].X, ownerLocation.Y + _component->Points[i].Y));
		point.setFillColor(sf::Color::Red);
		WindowRef->draw(point);
		// end debug
	}

	SetCollidingState(drawShape, _component->GetOwner());

	drawShape.setFillColor(sf::Color(_component->ObjectColor.R, _component->ObjectColor.G,
		_component->ObjectColor.B, _component->ObjectColor.A));
	drawShape.setRotation(_component->GetOwner()->GetTransform().Rotation);

	if (_component->texturePath != "")
	{
		if (!Application::Get().GetTextureMgr()->IsTextureLoaded(_component->name))
		{
			Application::Get().GetTextureMgr()->LoadTexture(_component->name, _component->texturePath);
		}
		
		sf::Texture* texture = &Application::Get().GetTextureMgr()->GetTexture(_component->name);
		drawShape.setTexture(texture);
	}
}

void SfmlWindow::SetCollidingState(sf::Shape& _shape, SActor* _actor)
{
	if (_actor->bIsColliding)
	{
		_shape.setOutlineColor(sf::Color::Red);
	}
	else
	{
		_shape.setOutlineColor(sf::Color::Green);
	}

	if ( _actor->bIsStatic )
	{
		_shape.setOutlineColor(sf::Color::Magenta);
	}

	_shape.setOutlineThickness(1);
}

void SfmlWindow::SetCommonShapeProperties(sf::Shape& _shape, SShapeComponent* _component)
{
	//_shape.setFillColor(sf::Color(_component->ObjectColor.R, _component->ObjectColor.G,
		//_component->ObjectColor.B, _component->ObjectColor.A));

	_shape.setFillColor(sf::Color(0, 0, 0, 0));
	_shape.setPosition(sf::Vector2f(_component->GetOwner()->GetLocation().X, _component->GetOwner()->GetLocation().Y));
	_shape.setRotation(_component->GetOwner()->GetTransform().Rotation);

	SetCollidingState(_shape, _component->GetOwner());
}

void SfmlWindow::Init(const WindowsProps& props)
{
	m_Data.Title = props.Title;
	m_Data.Height = props.Height;
	m_Data.Width = props.Width;

	WindowRef = new sf::RenderWindow(sf::VideoMode(m_Data.Width, m_Data.Height), m_Data.Title);
	WindowRef->setFramerateLimit(Configuration::FrameRate);
	WindowRef->setVerticalSyncEnabled(Configuration::VerticalSync);

	// TODO faire la window imgui here so it will be better for setting and get the button.
	ImGui::SFML::Init(*WindowRef);
	ImPlot::CreateContext();
}

void SfmlWindow::Shutdown()
{
	ImPlot::DestroyContext();
	ImGui::SFML::Shutdown();
	WindowRef->close();
}

// utility structure for realtime plot
struct RollingBuffer {
	float Span;
	ImVector<ImVec2> Data;
	RollingBuffer() {
		Span = 10.0f;
		Data.reserve(2000);
	}
	void AddPoint(float x, float y) {
		float xmod = fmodf(x, Span);
		if (!Data.empty() && xmod < Data.back().x)
			Data.shrink(0);
		Data.push_back(ImVec2(xmod, y));
	}
};

void SfmlWindow::HandleEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		KeyPressedEvent tmpevent(event.key.scancode);
		EventCallBack(tmpevent);
	}
	else if (event.type == sf::Event::Closed)
	{
		WindowCloseEvent tmpevent;
		EventCallBack(tmpevent);
	}
	else if (event.type == sf::Event::Resized)
	{
		WindowResizeEvent tmpevent(event.size.width, event.size.height);
		EventCallBack(tmpevent);
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		MouseMovedEvent tmpevent(FVector2D(event.mouseMove.x, event.mouseMove.y));
		EventCallBack(tmpevent);
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		MouseButtonPressedEvent tmpevent(event.mouseButton.button);
		EventCallBack(tmpevent);
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		MouseButtonReleasedEvent tmpevent(event.mouseButton.button);
		EventCallBack(tmpevent);
	}
	// TODO mettre le reste des events qui pourrais servire ici.
}


// TODO faire des classe et fonction plus jolie pour nos bouton ImGui
void SfmlWindow::DrawImGuiWin()
{
	ImGuiWindowFlags imFlags =
		ImGuiWindowFlags_NoDecoration
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_AlwaysAutoResize
		| ImGuiWindowFlags_NoSavedSettings
		| ImGuiWindowFlags_NoFocusOnAppearing
		| ImGuiWindowFlags_NoNav;
	//ImGui::SetNextWindowSize(sf::Vector2f(200, 200));
	ImGui::SetNextWindowPos(sf::Vector2f(0,0));
	ImGui::SetNextWindowBgAlpha(0.0f);

	ImGui::Begin("Debugs");

	// ImGui::Button("Tile Type");
	sf::Time currentTime = m_ClockDraw.getElapsedTime();
	m_ClockDraw.restart();
	const int DrawTime = currentTime.asMilliseconds();
	const int TickTime = m_TimeLogic.asMilliseconds();
	double curr = ImGui::GetTime();
	const int targetSec = 2;

	ImGui::Text("Draw Time : %d ms", DrawTime);
	ImGui::Text("Logic Time : %d ms", TickTime);

	ImGui::Separator();

	bool vertSync = Configuration::VerticalSync;
	ImGui::Checkbox("Vertical Sync", &vertSync);
	if (vertSync != Configuration::VerticalSync)
	{
		Configuration::VerticalSync = vertSync;
		WindowRef->setVerticalSyncEnabled(Configuration::VerticalSync);
	}
	int frameRate = Configuration::FrameRate; 
	ImGui::InputInt("Frame rate", &frameRate);
	if (frameRate != Configuration::FrameRate)
	{
		Configuration::FrameRate = frameRate;
		WindowRef->setFramerateLimit(Configuration::FrameRate);
	}

	ImGui::Separator();

	Graph.push_back(FVector2D(curr, DrawTime));
	if (Graph.size() > Configuration::FrameRate * targetSec)
	{
		Graph.erase(Graph.begin());
	}
	TickGraph.push_back(FVector2D(curr, TickTime));
	if (TickGraph.size() > Configuration::FrameRate * targetSec)
	{
		TickGraph.erase(TickGraph.begin());
	}

	// Begin the ImPlot graph
	if(ImPlot::BeginPlot("Perf Graph", "Time", "Milliseconds"))
	{
		ImPlot::SetupAxisScale(ImAxis_X1, 10);
		ImPlot::SetupAxisLimits(ImAxis_X1, curr - targetSec, curr + 0.1, ImGuiCond_Always);
		ImPlot::SetupAxisLimits(ImAxis_Y1, -0.5, 25, ImGuiCond_Always);
		ImPlot::PlotLine("Draw Time", &Graph[0].X, &Graph[0].Y, Graph.size() - 1, 0, 0, sizeof(FVector2D));
		ImPlot::PlotLine("Tick Time", &TickGraph[0].X, &TickGraph[0].Y, TickGraph.size() - 1, 0, 0, sizeof(FVector2D));
		ImPlot::EndPlot();
	}

	ImGui::End();
}
