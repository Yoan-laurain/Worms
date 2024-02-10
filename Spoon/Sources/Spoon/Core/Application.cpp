#include "Application.h"
#include "Level.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Inputs/InputMgr.h"
#include "Objects/SActor.h"
#include "Renders/SFML/TextureMgr.h"
#include "Library/TColor.h"
#include "Objects/Prefab/RectangleObject.h"
#include "Objects/Components/SShapeComponent.h"
#include "Objects/Prefab/CircleObject.h"
#include "Widgets/WidgetManager.h"

Application* Application::s_Instance = nullptr;

Application::Application() : 
	ScreenSize(FVector2D(720, 1080)),
	WindowName("SpoonEngine"),
	_InputMgr(nullptr),
	_TextureMgr(nullptr)
{
	s_Instance = this;
	Init();
}

Application::Application(const std::string& windowName, const FVector2D screensize) : ScreenSize(screensize), WindowName(windowName)
{
	s_Instance = this;
	Init();
}

Application::~Application()
{
	SetLevel(nullptr, true);
	delete _InputMgr;
	delete _TextureMgr;
}

void Application::Init()
{
	WindowsProps win(WindowName, ScreenSize.X, ScreenSize.Y);
	m_WindowRef = Window::Create(win);
	m_WindowRef->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	m_WindowRef->SetEventRenderBack(std::bind(&Application::OnRender, this));

	_InputMgr = new InputMgr();
	_InputMgr->Init();
	_TextureMgr = new TextureMgr();
}

void Application::Run()
{
	if (CurrentLevel)
	{
		CurrentLevel->BeginPlay();
	}
	std::thread LogicThread(std::bind(&Application::TickRun, this));
	LogicThread.detach();
	while (bIsRunning)
	{
		m_WindowRef->OnRender();
	}
}

void Application::OnEvent(SpoonEvent& e)
{
	EventDispatcher dispatcher(e);

	// Todo : � sup lorsque les key seront bien impl
	//for (const auto& tmp : GetWorld()->EntityList)
	//{
	//	//tmp->OnEvent(e);
	//}

	dispatcher.Dispatch<AppTickEvent>(BIND_EVENT_FN(Application::OnAppTick));

	//dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(Application::OnKeyPressed));

	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

	//dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(Application::OnMouseMoved));

	dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(Application::OnMousePressed));

}

void Application::SetLevel(class Level* _newLevel, const bool DestroyPrevious /*= false*/)
{
	if (DestroyPrevious && CurrentLevel)
	{
		delete CurrentLevel;
	}
	CurrentLevel = _newLevel;
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	bIsRunning = false;
	return true;
}

bool Application::OnKeyPressed(KeyPressedEvent& e)
{
#if DEBUG
	std::cout << e.ToString() << std::endl;
#endif // DEBUG

	// Resend les event � tous les objets qui poss�de un bind
	// je sais pas encore vraiment faudrait que je fasse un system de listerner
	// comme �a des que la fonction et call pouf je call tous les autres.
	return true;
}

bool Application::OnAppTick(AppTickEvent& e)
{
	_InputMgr->Update(e.GetDeltaTime());
	CurrentLevel->UpdateEntity(e.GetDeltaTime());
	return true;
}

void Application::OnRender()
{
	// Todo : I should probably put a wait for the entity list to be construct to render
	if (!GetWorld()->bIsListBeingEdit)
	{
		for (const auto& CurrentActor : GetWorld()->EntityList)
		{
			if (m_WindowRef)
				m_WindowRef->Draw(CurrentActor.get());
		}
	}

#if DEBUG
	if (m_WindowRef)
	{
		m_WindowRef->DrawAllDebugs(GetWorld()->DebugShapes);
		GetWorld()->ClearDebugShapes();
	}

#endif
}

void Application::AddNewPlayer(SPlayer* player)
{
	Players.push_back(player);

	_InputMgr->AddNewPlayer();
}

FVector2D Application::GetScreenSize() const
{ 
	return ScreenSize;
}

Window* Application::GetWindow() const
{
	return m_WindowRef;
}

bool Application::BindAction(SPlayer* player, InputAction inputAction, std::function<void(float)> func, InputType inputType)
{
	int index = -1;
	for (int i = 0; i < Players.size(); ++i)
	{
		if (Players[i] == player)
		{
			index = i;
		}
	}

#if _DEBUG
	assert(index != -1);
#else
	if (index == -1)
	{
		return false;
	}
#endif

	_InputMgr->BindAction(index, inputAction, func,inputType);
	return true;
}

InputMgr* Application::GetInputMgr() const
{
	return _InputMgr;
}

TextureMgr* Application::GetTextureMgr() const
{
	return _TextureMgr;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
	return true;
}

bool Application::OnMouseMoved(MouseMovedEvent& e)
{
	for (const auto& currentActor : CurrentLevel->EntityList)
	{
		currentActor->IsInBound(e.GetLoc());
	}
	return false;
}

bool Application::OnMousePressed(MouseButtonPressedEvent& e)
{
	if (e.GetMouseButton() == Mouse::Button3 ) 
	{
		float width = rand() % 30 + 5;
		float height = rand() % 30 + 5;
		
		m_WindowRef->GetMousePos();

		FColor color = FColor(rand() % 255, rand() % 255, rand() % 255, 255);

		std::unique_lock<std::mutex> lock(_mutex);
		SRectangleObject* rect = GetWorld()->SpawnActor<SRectangleObject>(FTransform(m_WindowRef->GetMousePos(), FVector2D(width, height)));
		rect->GetComponent<SShapeComponent>()->ObjectColor = color;
	}
	else if (e.GetMouseButton() == Mouse::Button4)
	{
		float radius = rand() % 30 + 5;

		m_WindowRef->GetMousePos();

		FColor color = FColor(rand() % 255, rand() % 255, rand() % 255, 255);

		std::unique_lock<std::mutex> lock(_mutex);
		SCircleObject* circle = GetWorld()->SpawnActor<SCircleObject>(FTransform(m_WindowRef->GetMousePos(), FVector2D(radius, radius)));
		circle->GetComponent<SShapeComponent>()->ObjectColor = color;
	}
	else if (e.GetMouseButton() == Mouse::Button0)
	{
		WidgetManager::GetInstance()->HandleWidgetOnClicked(m_WindowRef->GetMousePos());
	}
	
	return true;
}

void Application::TickRun()
{
	while (bIsRunning)
	{
		if (m_WindowRef)
		{
			m_WindowRef->OnUpdate();
		}
	}
}

Level* Application::GetWorld() const
{
	return CurrentLevel;
}
