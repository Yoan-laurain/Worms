#pragma once
#include "Core/Core.h"
#include "Events/SpoonEvent.h"
#include "Library/TVector.h"
#include "Library/TStruct.h"

enum DebugShape;
struct DebugShapeData;

struct WindowsProps
{
	std::string Title;

	uint32 Width;
	unsigned int Height;

	template <typename GivenSize = uint32>
	WindowsProps(const std::string& title = "SpoonEngine",
				GivenSize width = 1280,
				GivenSize height = 720)
			: Title(title), Width(static_cast<uint32>(width)), Height(static_cast<uint32>(height))
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
	FVector2D GetMousePos() const { return m_mousePos; }

	static Window* Create(const WindowsProps& props = WindowsProps());

#if DEBUG
	virtual void DrawAllDebugs(std::vector<DebugShapeData>& DebugShapes) = 0;
	virtual void DrawDebugPoint(const FTransform& Transform) = 0;
#endif

protected:
	FVector2D m_mousePos;
};