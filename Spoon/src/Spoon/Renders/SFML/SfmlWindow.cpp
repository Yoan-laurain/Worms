#include "SfmlWindow.h"
#include "Object/SActor.h"
#include "Spoon/Events/KeyEvent.h"
#include "Spoon/Events/ApplicationEvent.h"
#include "Spoon/Events/MouseEvent.h"

#ifndef DEBUG
#include "imgui.h"
#include <imgui-SFML.h>
#endif // !DEBUG

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
	if (_currentActor == nullptr)
	{
		return;
	}

	sf::RectangleShape _currentShape;

	_currentShape.setSize(sf::Vector2f(_currentActor->GetSize().X, _currentActor->GetSize().Y));
	_currentShape.setFillColor(sf::Color(_currentActor->GetColor().R, _currentActor->GetColor().G, _currentActor->GetColor().B, _currentActor->GetColor().A));
	_currentShape.setPosition(sf::Vector2f(_currentActor->GetLocation().X, _currentActor->GetLocation().Y));

	if (WindowRef != nullptr)
	{
		WindowRef->draw(_currentShape);
	}

	return;
}

unsigned int SfmlWindow::GetWidth() const
{
	return m_Data.Width;
}

unsigned int SfmlWindow::GetHeight() const
{
	return m_Data.Height;
}

void SfmlWindow::Init(const WindowsProps& props)
{
	m_Data.Title = props.Title;
	m_Data.Height = props.Height;
	m_Data.Width = props.Width;

	WindowRef = new sf::RenderWindow(sf::VideoMode(m_Data.Width, m_Data.Height), m_Data.Title);

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
