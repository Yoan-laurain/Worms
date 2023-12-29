#include "Application.h"
#include "Level.h"

#include "Objects/SActor.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Inputs/InputMgr.h"

Application* Application::s_Instance = nullptr;

Application::Application() : 
	WindowName("SpoonEngine"),
	ScreenSize(FVector2D(720, 1080)),
	_InputMgr(nullptr),
	_TextureMgr(nullptr)
{
	s_Instance = this;
	Init();
}

Application::Application(std::string windowName, FVector2D screensize) : WindowName(windowName), ScreenSize(screensize)
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

	// Todo : à sup lorsque les key seront bien impl
	for (const auto& tmp : GetWorld()->EntityList)
	{
		tmp->OnEvent(e);
	}

	dispatcher.Dispatch<AppTickEvent>(BIND_EVENT_FN(Application::OnAppTick));

	//dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(Application::OnKeyPressed));

	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

	//dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(Application::OnMouseMoved));

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

	// Resend les event à tous les objets qui possède un bind
	// je sais pas encore vraiment faudrait que je fasse un system de listerner
	// comme ça des que la fonction et call pouf je call tous les autres.
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
	for (const auto& CurrentActor : GetWorld()->EntityList)
	{
		if(m_WindowRef)
			m_WindowRef->Draw(CurrentActor.get());
	}
	return;
}

void Application::AddNewPlayer(SPlayer* player)
{
	Players.push_back(player);

	_InputMgr->AddNewPlayer();
}

bool Application::BindAction(SPlayer* player, InputAction inputAction, std::function<void(float)> func)
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

	_InputMgr->BindAction(index, inputAction, func);
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

void Application::TickRun()
{
	while (bIsRunning)
	{
		if(m_WindowRef)
			m_WindowRef->OnUpdate();
	}
}

Level* Application::GetWorld() const
{
	return CurrentLevel;
}
