#pragma once
#include "Spoon/Core/Core.h"
#include "Spoon/Events/SpoonEvent.h"

struct WindowsProps
{
	std::string Title;

	uint Width;
	unsigned int Height;

	template <typename GivenSize = uint>
	WindowsProps(const std::string& title = "SpoonEngine",
				GivenSize width = 1280,
				GivenSize height = 720)
			: Title(title), Width(static_cast<uint>(width)), Height(static_cast<uint>(height))
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

