#include "SfmlWindow.h"
#include "Objects/SActor.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Objects/Components/SShapeComponent.h"
#include "TextureMgr.h"
#include "Widgets/WidgetManager.h"
#include "Core/Application.h"
#include "..\..\Widgets\Renderer\SFML\SFMLWidgetRenderer.h"
#include "..\..\Widgets\Renderer\ImGui\ImGuiWidgetRenderer.h"
#include "..\..\Widgets\Renderer\DrawingWidgetInterfaceManager.h"
#include <Renders/SFML/SfmlWindow.h>
#include <imgui.h>
#include <imgui-SFML.h>
#include <implot.h>
#include <Windows.h>

#include <Core/Level.h>

// Todo faire un vrai truc pour un bon fichier config pour l'engine :/
namespace Configuration
{
	int FrameRate = 60;
	bool VerticalSync = false;
}

// Function call de maniere indirect lorsque j'ai besoin de la fenetre.
Window* Window::Create(const WindowsProps& props)
{
	return new SfmlWindow(props);
}

// Creation d'une nouvelle fenetre call init page
SfmlWindow::SfmlWindow(const WindowsProps& props) :
	WidgetInterfaceSelectedIndex( new char[10] ),
	WidgetInterfaceSelectedPreviousIndex( new char[10] ),
	WidgetDrawingInterfaces(),
	bIsHoveringSomething(false)
{
	Init(props);

	WidgetDrawingInterfaces["SFML"] = std::make_shared<SFMLWidgetRenderer>();
	WidgetDrawingInterfaces["ImGUI"] = std::make_shared<ImGuiWidgetRenderer>();
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

	HandleCursorState();
	m_ClockDraw.restart();
	WindowRef->clear();

	EventRenderBack();

	ImGui::SFML::Update(*WindowRef, m_GlobalClock.getElapsedTime());
	m_GlobalClock.restart();

	m_DrawTime = m_ClockDraw.getElapsedTime().asSeconds() * 1000.f;

	WidgetManager::GetInstance()->GetWidgetToRender();
	DrawImGuiWin();
	ImGui::SFML::Render(*WindowRef);

	HandleSelectedWidgetInterfaceChanged();

	WindowRef->display();
}

void SfmlWindow::Draw(const SActor* _currentActor)
{
	if (_currentActor == nullptr || WindowRef == nullptr)
	{
		return;
	}
	std::vector<SShapeComponent*> CompList;

	std::unique_lock<std::mutex> lock(_mutex);
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

#if DEBUG
void SfmlWindow::DrawDebugPoint(const FTransform& transform)
{
	std::unique_lock<std::mutex> lock(_mutex);
	sf::CircleShape circle;
	circle.setRadius(transform.Size.X);
	circle.setOrigin(transform.Size.X, transform.Size.Y);
	circle.setPosition(sf::Vector2f(transform.Location.X, transform.Location.Y));
	circle.setFillColor(sf::Color::Red);
	circle.setOutlineColor(sf::Color::Green);
	circle.setOutlineThickness(1);
	WindowRef->draw(circle);
}

void SfmlWindow::DrawAllDebugs(std::vector<DebugShapeData>& DebugShapes)
{
	for (auto& shape : DebugShapes)
	{
		switch (shape.Shape)
		{
			case DebugShape::SPHERE :
					DrawDebugPoint(shape.Transform);
					break;
				default:
					break;
		}
	}
}

#endif

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

	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(_component->GetOwner()->GetLocation().X, _component->GetOwner()->GetLocation().Y)),
		sf::Vertex(sf::Vector2f(_component->GetOwner()->GetLocation().X + _component->Radius, _component->GetOwner()->GetLocation().Y + _component->Radius))
	};

	WindowRef->draw(line, 2, sf::Lines);

	SetCommonShapeProperties(_circle, _component);
}

void SfmlWindow::DrawConvex(SPolygonComponent* _component, sf::ConvexShape& drawShape)
{
	drawShape.setPointCount(_component->Points.size());	

	FVector2D ownerLocation = _component->GetOwner()->GetLocation();

	for (int i = 0; i < _component->Points.size(); i++)
	{
		drawShape.setPoint(i, sf::Vector2f(ownerLocation.X + _component->Points[i].X, ownerLocation.Y + _component->Points[i].Y));

#if DEBUG
		sf::CircleShape point( 3 );
		point.setOrigin( 3, 3 );
		point.setPosition(sf::Vector2f(ownerLocation.X + _component->Points[i].X, ownerLocation.Y + _component->Points[i].Y));
		point.setFillColor(sf::Color::White);
		WindowRef->draw(point);
#endif
	}

	SetCollidingState(drawShape, _component->GetOwner());

	if (_component->texturePath != "")
	{
		if (!Application::Get().GetTextureMgr()->IsTextureLoaded(_component->texturePath))
		{
			Application::Get().GetTextureMgr()->LoadTexture(_component->texturePath, _component->texturePath);
		}
		
		sf::Texture* texture = &Application::Get().GetTextureMgr()->GetTexture(_component->texturePath);
		drawShape.setTexture(texture);
	}

	if (_component->texturePath != "" && _component->ObjectColor.A == 0.f)
		return;

	drawShape.setFillColor(sf::Color(_component->ObjectColor.R, _component->ObjectColor.G,
		_component->ObjectColor.B, _component->ObjectColor.A));

}

void SfmlWindow::SetCollidingState(sf::Shape& _shape, SActor* _actor)
{
#if DEBUG
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
#endif
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

void SfmlWindow::RenderDrawable(sf::Drawable& _drawable)
{
	WindowRef->draw(_drawable);
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
		m_mousePos = tmpevent.GetLoc();

		WidgetManager::GetInstance()->HandleWidgetHoverState(m_mousePos, bIsHoveringSomething);
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
	ImGui::SetNextWindowPos(sf::Vector2f(0,0));

	ImGui::Begin("Debugs");

	const float TickTime = m_TimeLogic.asSeconds() * 1000.f;
	double curr = ImGui::GetTime();
	const int targetSec = 2;
	int currFrameRate = 1000.f / m_DrawTime;
	if (m_bFrameLimitActivated)
	{
		currFrameRate = std::clamp(currFrameRate, 0, Configuration::FrameRate);
	}
	ImGui::Text("Draw Time : %.2f ms, FPS : %d", m_DrawTime, currFrameRate);
	ImGui::Text("Logic Time : %.2f ms", TickTime);

	ImGui::Text("Entity count : %d", Application::Get().GetWorld()->GetEntityCount());

	ImGui::Separator();

	bool vertSync = Configuration::VerticalSync;
	ImGui::Checkbox("Vertical Sync", &vertSync);
	if (vertSync != Configuration::VerticalSync)
	{
		Configuration::VerticalSync = vertSync;
		WindowRef->setVerticalSyncEnabled(Configuration::VerticalSync);
	}

	ImGui::Checkbox("Frame Limit", &m_bFrameLimitActivated);
	if (m_bFrameLimitActivated)
	{
		int frameRate = Configuration::FrameRate;
		ImGui::InputInt("Frame rate", &frameRate);
		if (frameRate != Configuration::FrameRate)
		{
			Configuration::FrameRate = frameRate;
			WindowRef->setFramerateLimit(Configuration::FrameRate);
		}
	}
	 
	ImGui::Separator();

	static const char* current_item = WidgetInterfaceSelectedIndex; 

	if (ImGui::BeginCombo("Widget Interface", current_item))
	{
		for (auto& [key, value] : WidgetDrawingInterfaces)  
		{
			bool is_selected = (current_item == key); 
			if (ImGui::Selectable(key, is_selected))
			{
				current_item = key; 
				strcpy(WidgetInterfaceSelectedIndex, key);
			}

			if (is_selected)
			{
				ImGui::SetItemDefaultFocus(); 
			}
		}

		ImGui::EndCombo();
	}

	ImGui::Separator();

	// Ici y a un pb avec le faite de pouvoir changer le frame rate.
	Graph.push_back(FVector2D(curr, m_DrawTime));
	ImGui::Text("Graph Size : %f", curr);
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
		//ImPlot::SetupAxisScale(ImAxis_X1, 10);
		ImPlot::SetupAxisLimits(ImAxis_X1, curr - targetSec, curr + 0.1, ImGuiCond_Always);
		//ImPlot::SetupAxisLimits(ImAxis_Y1, -0.5, 5, ImGuiCond_Always);
		ImPlot::PlotLine("Draw Time", &Graph[0].X, &Graph[0].Y, Graph.size() - 1, 0, 0, sizeof(FVector2D));
		ImPlot::PlotLine("Tick Time", &TickGraph[0].X, &TickGraph[0].Y, TickGraph.size() - 1, 0, 0, sizeof(FVector2D));
		ImPlot::EndPlot();
	}

	ImGui::End();
}

void SfmlWindow::HandleSelectedWidgetInterfaceChanged()
{
	if (strcmp( WidgetInterfaceSelectedPreviousIndex, WidgetInterfaceSelectedIndex) != 0)
	{
		SetWidgetDrawingInterface(WidgetInterfaceSelectedIndex);
	}
}

void SfmlWindow::OnWidgetInterfaceSet( const char* key, std::shared_ptr<DrawingWidgetInterface> value )
{
	strcpy(WidgetInterfaceSelectedIndex, key);
	strcpy(WidgetInterfaceSelectedPreviousIndex, WidgetInterfaceSelectedIndex);
			 
	DrawingWidgetInterfaceManager::getInstance().setWidgetDrawingInterface( value );
}

void SfmlWindow::SetWidgetDrawingInterface(const char* _interfaceName)
{
	for (auto& [key, value] : WidgetDrawingInterfaces)
	{
		if (strcmp(key, _interfaceName) == 0)
		{
			OnWidgetInterfaceSet( key, value );
			return;
		}
	}
	
	for (auto& [key, value] : WidgetDrawingInterfaces)
	{
		OnWidgetInterfaceSet( key, value );
		return;
	}

	std::cout << "Interface not found" << std::endl;
}

void SfmlWindow::HandleCursorState()
{
	SetCursor(LoadCursorA(NULL, bIsHoveringSomething ? IDC_HAND : IDC_ARROW));
}
