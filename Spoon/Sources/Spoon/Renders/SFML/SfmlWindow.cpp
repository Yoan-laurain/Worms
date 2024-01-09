#include "SfmlWindow.h"
#include "Objects/SActor.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Objects/Components/SShapeComponent.h"
#include "TextureMgr.h"

#ifndef DEBUG
#include <imgui.h>
#include <imgui-SFML.h>
#endif // !DEBUG
#include "Core/Application.h"

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
	sf::Time time = clock.getElapsedTime();
	clock.restart();
	_lock.unlock();
	AppTickEvent TickEvent(time.asSeconds());
	EventCallBack(TickEvent);
}

void SfmlWindow::OnRender()
{
	sf::Event event;
	while (WindowRef->pollEvent(event))
	{
#ifndef DEBUG
		ImGui::SFML::ProcessEvent(event);
#endif // !DEBUG
		// Todo maybe this function can be thread so the logic will still be separt with the render?
		HandleEvent(event);
	}

#ifndef DEBUG
	ImGui::SFML::Update(*WindowRef, clock.getElapsedTime());
#endif // !DEBUG

	WindowRef->clear();

#ifndef DEBUG
	DrawImGuiWin();
#endif // !DEBUG

	EventRenderBack();

#ifndef DEBUG
	ImGui::SFML::Render(*WindowRef);
#endif // !DEBUG

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

	_shape.setOutlineThickness(3);
}

void SfmlWindow::SetCommonShapeProperties(sf::Shape& _shape, SShapeComponent* _component)
{
	//_shape.setFillColor(sf::Color(_component->ObjectColor.R, _component->ObjectColor.G,
		//_component->ObjectColor.B, _component->ObjectColor.A));

	_shape.setFillColor(sf::Color(0, 0, 0, 0));
	_shape.setPosition(sf::Vector2f(_component->GetOwner()->GetLocation().X, _component->GetOwner()->GetLocation().Y));

	SetCollidingState(_shape, _component->GetOwner());
}

void SfmlWindow::Init(const WindowsProps& props)
{
	m_Data.Title = props.Title;
	m_Data.Height = props.Height;
	m_Data.Width = props.Width;

	WindowRef = new sf::RenderWindow(sf::VideoMode(m_Data.Width, m_Data.Height), m_Data.Title);
	WindowRef->setFramerateLimit(60);
	WindowRef->setVerticalSyncEnabled(true);

	// TODO faire la window imgui here so it will be better for setting and get the button.
#ifndef DEBUG
	ImGui::SFML::Init(*WindowRef);
#endif // !DEBUG

}

void SfmlWindow::Shutdown()
{
#ifndef DEBUG
	ImGui::SFML::Shutdown();
#endif // !DEBUG
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

#ifndef DEBUG
void SfmlWindow::DrawImGuiWin()
{
	ImGuiWindowFlags imFlags =
		ImGuiWindowFlags_NoDecoration
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_AlwaysAutoResize
		| ImGuiWindowFlags_NoSavedSettings
		| ImGuiWindowFlags_NoFocusOnAppearing
		| ImGuiWindowFlags_NoNav;
	ImGui::SetNextWindowSize(sf::Vector2f(50,50));
	ImGui::SetNextWindowPos(sf::Vector2f(0,0));
	ImGui::SetNextWindowBgAlpha(0.5f);

	ImGui::Begin("Tools");

	ImGui::Button("Tile Type");

	ImGui::End();
}
#endif // !DEBUG
