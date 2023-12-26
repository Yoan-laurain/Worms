#pragma once
#include "Spoon/Core/Core.h"
#include "Spoon/Events/SpoonEvent.h"

struct WindowsProps
{
	std::string Title;

	unsigned int Width;
	unsigned int Height;

	WindowsProps(const std::string& title = "SpoonEngine",
				unsigned int width = 1280,
				unsigned int height = 720)
			: Title(title), Width(width), Height(height)
	{}
};

class SPOON_API Window
{
public:
	using EventCallBackFn = std::function<void(SpoonEvent&)>;

	virtual ~Window() {};

	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
	virtual void Draw(const class SActor* _currentActor) = 0;
	virtual void SetEventCallback(const EventCallBackFn& callback) = 0;
	virtual void SetEventRenderBack(const std::function<void()>& callback) = 0;
	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;

	static Window* Create(const WindowsProps& props = WindowsProps());
};

