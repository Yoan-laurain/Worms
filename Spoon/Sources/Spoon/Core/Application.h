#pragma once
#include "Core.h"
#include "Library/TVector.h"
#include <snpch.h>

class Level;
class Window;
class SpoonEvent;
class SPlayer;
enum class InputAction;
class WindowCloseEvent;
class KeyPressedEvent;
class AppTickEvent;
class WindowResizeEvent;
class MouseMovedEvent;
class InputMgr;
class TextureMgr;

class SPOON_API Application
{
public:

	Application();

	Application(std::string windowName, FVector2D screensize);

	virtual ~Application();

	void Init();

	void Run();

	// Dispatch Event
	void OnEvent(SpoonEvent& e);

	Level* GetWorld() const;

	static Application& Get() { return *s_Instance; }

	class InputMgr* GetInputMgr() const;
	class TextureMgr* GetTextureMgr() const;

	void AddNewPlayer(SPlayer* player);

	bool BindAction(SPlayer* player,InputAction inputAction, std::function<void(float)> func);

	FVector2D GetScreenSize() const;

protected:

	void SetLevel(Level* _newLevel, const bool DestroyPrevious = false);

private:

	// Event
	bool OnWindowClose(WindowCloseEvent& e);
	bool OnKeyPressed(KeyPressedEvent& e);
	bool OnAppTick(AppTickEvent& e);
	bool OnWindowResize(WindowResizeEvent& e);
	bool OnMouseMoved(MouseMovedEvent& e);

	void TickRun();
	void OnRender();

	#pragma region WindowProperty

	FVector2D ScreenSize;

	std::string WindowName;

	#pragma endregion

private:

	Window* m_WindowRef;

	bool bIsRunning = true;

	Level* CurrentLevel;

	static Application* s_Instance;

	std::vector<SPlayer*> Players;
	InputMgr* _InputMgr;
	TextureMgr* _TextureMgr;

};