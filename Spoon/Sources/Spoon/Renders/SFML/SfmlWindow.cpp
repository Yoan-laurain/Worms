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

#include "Widgets/Image/ImageWidget.h"

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

	WidgetManager::GetInstance()->RenderWidgets();
	DrawImGuiWin();
	ImGui::SFML::Render(*WindowRef);

	HandleSelectedWidgetInterfaceChanged();

	WindowRef->display();
}

void SfmlWindow::Draw(const SActor* CurrentActor)
{
	if (CurrentActor == nullptr || WindowRef == nullptr)
	{
		return;
	}
	std::vector<SShapeComponent*> CompList;

	std::unique_lock lock(_mutex);
	
	if(!CurrentActor->GetAllComponentType<SShapeComponent*>(CompList))
		return;

	for (SShapeComponent* Comp : CompList)
	{
		if (Comp->GetType() == ActorType_Polygon)
		{
			sf::ConvexShape DrawShape;
			DrawConvex(static_cast<SPolygonComponent*>(Comp), DrawShape);
			WindowRef->draw(DrawShape);
		}
		else if(Comp->GetType() == ActorType_Circle)
		{
			sf::CircleShape DrawShape;
			DrawCircle(static_cast<SCircleComponent*>(Comp), DrawShape);
			WindowRef->draw(DrawShape);
		}

		Comp->GetOwner()->bIsColliding = false;
	}
}

#if DEBUG
void SfmlWindow::DrawDebugPoint(const FTransform& Transform)
{
	std::unique_lock Lock(_mutex);
	
	sf::CircleShape Circle;
	
	Circle.setRadius(Transform.Size.X);
	Circle.setOrigin(Transform.Size.X, Transform.Size.Y);
	Circle.setPosition(sf::Vector2f(Transform.Location.X, Transform.Location.Y));
	Circle.setFillColor(sf::Color::Red);
	Circle.setOutlineColor(sf::Color::Green);
	Circle.setOutlineThickness(1);
	
	WindowRef->draw(Circle);
}

void SfmlWindow::DrawAllDebugs(std::vector<DebugShapeData>& DebugShapes)
{
	for (auto& Shape : DebugShapes)
	{
		switch (Shape.Shape)
		{
			case SPHERE :
					DrawDebugPoint(Shape.Transform);
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

void SfmlWindow::SetTexture(const SShapeComponent* Component, sf::Shape& Shape )
{
	if (!Component->TexturePath.empty())
	{
		if (!Application::Get().GetTextureMgr()->IsTextureLoaded(Component->TexturePath))
		{
			Application::Get().GetTextureMgr()->LoadTexture(Component->TexturePath, Component->TexturePath);
		}

		const sf::Texture* Texture = &Application::Get().GetTextureMgr()->GetTexture(Component->TexturePath);
		Shape.setTexture(Texture);
	}
}

void SfmlWindow::DrawCircle(SCircleComponent* Component, sf::CircleShape& Circle)
{
	Circle.setOrigin(Component->Origin.X * Component->Radius * 2, Component->Origin.Y * Component->Radius * 2);
	Circle.setRadius(Component->Radius);
	
	SetTexture(Component, Circle);

#if DEBUG

	sf::Vertex Line[] =
	{
		sf::Vertex(sf::Vector2f(Component->GetOwner()->GetLocation().X, Component->GetOwner()->GetLocation().Y)),
		sf::Vertex(sf::Vector2f(Component->GetOwner()->GetLocation().X + Component->Radius, Component->GetOwner()->GetLocation().Y + Component->Radius))
	};

	WindowRef->draw(Line, 2, sf::Lines);

#endif
	
	SetCommonShapeProperties(Circle, Component);
}

void SfmlWindow::DrawConvex(const SPolygonComponent* Component, sf::ConvexShape& DrawShape)
{
	DrawShape.setPointCount(Component->Points.size());

	const FVector2D OwnerLocation = Component->GetOwner()->GetLocation();

	for (int i = 0; i < Component->Points.size(); i++)
	{
		DrawShape.setPoint(i, sf::Vector2f(OwnerLocation.X + Component->Points[i].X, OwnerLocation.Y + Component->Points[i].Y));

#if DEBUG
		sf::CircleShape point( 3 );
		
		point.setOrigin( 3, 3 );
		point.setPosition(sf::Vector2f(OwnerLocation.X + Component->Points[i].X, OwnerLocation.Y + Component->Points[i].Y));
		point.setFillColor(sf::Color::White);
		
		WindowRef->draw(point);
	}
	SetCollidingState(DrawShape, Component->GetOwner());

#endif
	
	SetTexture(Component, DrawShape);

	if (!Component->TexturePath.empty())
		return;

	DrawShape.setFillColor(sf::Color(Component->ObjectColor.R, Component->ObjectColor.G,
		Component->ObjectColor.B, Component->ObjectColor.A));

}

#if DEBUG
void SfmlWindow::SetCollidingState(sf::Shape& Shape, const SActor* Actor)
{
	Shape.setOutlineColor(Actor->bIsColliding ? sf::Color::Red : sf::Color::Green);
	Shape.setOutlineThickness(1);
	
	if ( Actor->bIsStatic )
	{
		Shape.setOutlineColor(sf::Color::Magenta);
	}
}
#endif

void SfmlWindow::SetCommonShapeProperties(sf::Shape& Shape, const SShapeComponent* Component)
{
	if (Component->TexturePath.empty())
	{
		Shape.setFillColor(sf::Color(Component->ObjectColor.R, Component->ObjectColor.G,
			Component->ObjectColor.B, Component->ObjectColor.A));
	}

	Shape.setPosition(sf::Vector2f(Component->GetOwner()->GetLocation().X, Component->GetOwner()->GetLocation().Y));
	Shape.setRotation(Component->GetOwner()->GetTransform().Rotation);
	
#if DEBUG
	SetCollidingState(Shape, Component->GetOwner());
#endif
}

void SfmlWindow::RenderDrawable(const sf::Drawable& Drawable)
{
	WindowRef->draw(Drawable);
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

void SfmlWindow::OnWidgetInterfaceSet( const char* Key, const std::shared_ptr<DrawingWidgetInterface>& Value )
{
	strcpy(WidgetInterfaceSelectedIndex, Key);
	strcpy(WidgetInterfaceSelectedPreviousIndex, WidgetInterfaceSelectedIndex);
			 
	DrawingWidgetInterfaceManager::GetInstance().SetWidgetDrawingInterface( Value );
}

void SfmlWindow::SetWidgetDrawingInterface(const char* InterfaceName)
{
	for (auto& [Key, Value] : WidgetDrawingInterfaces)
	{
		if (strcmp(Key, InterfaceName) == 0)
		{
			OnWidgetInterfaceSet( Key, Value );
			return;
		}
	}
	
	for (auto& [Key, Value] : WidgetDrawingInterfaces)
	{
		OnWidgetInterfaceSet( Key, Value );
		return;
	}

	assert(false, "No widget drawing interface found");
}

sf::Sprite& SfmlWindow::GetSprite(const ImageWidget& Image)
{
	if (!Application::Get().GetTextureMgr()->IsTextureLoaded(Image.ImagePath))
	{
		Application::Get().GetTextureMgr()->LoadTexture(Image.ImagePath, Image.ImagePath);
	}
	
	sf::Texture& Texture = Application::Get().GetTextureMgr()->GetTexture(Image.ImagePath);

	sf::Sprite* Sprite = new sf::Sprite();
	
	Sprite->setOrigin(Texture.getSize().x / 2.f, Texture.getSize().y / 2.f);
	Sprite->setPosition(Image.WorldPosition.X + Image.Size.X / 2.f, Image.WorldPosition.Y + Image.Size.Y / 2.f);
	Sprite->setScale(Image.Size.X / Texture.getSize().x, Image.Size.Y / Texture.getSize().y);
	Sprite->setTexture(Texture);
	Sprite->setRotation(Image.Rotation);

	return *Sprite;
}

void SfmlWindow::HandleCursorState()
{
	SetCursor(LoadCursorA(NULL, bIsHoveringSomething ? IDC_HAND : IDC_ARROW));
}