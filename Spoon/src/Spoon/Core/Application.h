#pragma once
#include "Core.h"
#include "Spoon/Library/TVector.h"
#include <snpch.h>

class Level;
class Window;


class SPOON_API Application
{
public:

	Application();

	Application(std::string windowName, FVector2D screensize);

	virtual ~Application();

	void Init();

	void Run();

	// Dispatch Event
	void OnEvent(class SpoonEvent& e);

	Level* GetWorld() const;

	__forceinline static Application& Get() { return *s_Instance; }

protected:

	void SetLevel(class Level* _newLevel, const bool DestroyPrevious = false);

private:

	// Event
	bool OnWindowClose(class WindowCloseEvent& e);
	bool OnKeyPressed(class KeyPressedEvent& e);
	bool OnAppTick(class AppTickEvent& e);
	bool OnWindowResize(class WindowResizeEvent& e);
	bool OnMouseMoved(class MouseMovedEvent& e);

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

};

