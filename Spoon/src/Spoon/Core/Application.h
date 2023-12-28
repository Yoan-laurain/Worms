#pragma once
#include "Core.h"
#include "Spoon/Library/TVector.h"
#include <snpch.h>
#include "Player.h"
#include <Spoon/Input/InputMgr.h>
#include <Spoon/Renders/SFML/TextureMgr.h>

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

	static Application& Get() { return *s_Instance; }

	InputMgr* GetInputMgr() const;
	TextureMgr* GetTextureMgr() const;

	void AddNewPlayer(Player* player);

	bool BindAction(Player* player, InputAction inputAction, std::function<void(float)> func);

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

	std::vector<Player*> Players;
	InputMgr* _InputMgr;
	TextureMgr* _TextureMgr;

};