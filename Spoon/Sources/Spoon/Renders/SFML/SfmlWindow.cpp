#include "SfmlWindow.h"
#include "Objects/SActor.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Objects/Components/SShapeComponent.h"

#ifndef DEBUG
#include "imgui.h"
#include <imgui-SFML.h>
#endif // !DEBUG
#include <Core/Application.h>

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
	Textures.clear();

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
		if (comp->GetType() == FActorType::ActorType_Rectangle)
		{
			sf::RectangleShape drawShape;
			DrawRectangle(static_cast<SRectangleComponent*>(comp), drawShape);
			WindowRef->draw(drawShape);
		}
		else if (comp->GetType() == FActorType::ActorType_Convex)
		{
			sf::ConvexShape drawShape;
			DrawConvex(static_cast<SConvexComponent*>(comp), drawShape);
			WindowRef->draw(drawShape);
		}
		else if (comp->GetType() == FActorType::ActorType_Sprite)
		{
			sf::Sprite drawSprite;
			DrawTexture(static_cast<SSpriteComponent*>(comp), drawSprite);
			WindowRef->draw(drawSprite);
		}
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

void SfmlWindow::DrawRectangle(const SRectangleComponent* _component, sf::RectangleShape& _currentShape)
{
	_currentShape.setSize(sf::Vector2f(_component->GetOwner()->GetSize().X, _component->GetOwner()->GetSize().Y));
	_currentShape.setFillColor(sf::Color(_component->ObjectColor.R, _component->ObjectColor.G,
		_component->ObjectColor.B, _component->ObjectColor.A));
	_currentShape.setPosition(sf::Vector2f(_component->GetOwner()->GetLocation().X, _component->GetOwner()->GetLocation().Y));
}

void SfmlWindow::DrawConvex(const SConvexComponent* _component, sf::ConvexShape& drawShape)
{
	drawShape.setPointCount(_component->Points.size());

	for (auto& point : _component->Points)
	{
		drawShape.setPoint(point.first, sf::Vector2f(point.second.X, point.second.Y));
	}

	drawShape.setFillColor(sf::Color(_component->ObjectColor.R, _component->ObjectColor.G,
		_component->ObjectColor.B, _component->ObjectColor.A));
}

void SfmlWindow::DrawTexture(SSpriteComponent* _component, sf::Sprite& sprite)
{
	Textures.push_back(sf::Texture());

	Application::Get().GetTextureMgr()->LoadTexture(_component->name, _component->texturePath, Textures.back());

	sprite.setColor(sf::Color(_component->ObjectColor.R, _component->ObjectColor.G,
		_component->ObjectColor.B, _component->ObjectColor.A));

	//sprite.setScale( _currentActor->GetSize().X / Textures.back().getSize().x, _currentActor->GetSize().Y / Textures.back().getSize().y);
	sprite.setPosition(sf::Vector2f(_component->GetOwner()->GetLocation().X, _component->GetOwner()->GetLocation().Y));

	sprite.setTexture(Textures.back());
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
