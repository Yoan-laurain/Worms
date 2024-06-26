#pragma once 

#include "Core/Core.h"
#include "snpch.h"


// Type d'event 0
enum class EventType
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

// Category d'event pour eviter de print un enorme mouseButtonPressed.
enum EventCategory
{
	None = 0,
	EventCategoryApplication = BIT(0),
	EventCategoryInput = BIT(1),
	EventCategoryKeyboard = BIT(2),
	EventCategoryMouse = BIT(3),
	EventCategoryMouseButton = BIT(4)
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

class SPOON_API SpoonEvent
{
	public:

	virtual ~SpoonEvent() = default;

	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); }

	inline bool IsInCategory(EventCategory category)
	{
		return GetCategoryFlags() & category;
	}

	bool Handle = false;
};

class EventDispatcher
{
public:
	EventDispatcher(SpoonEvent& event) : m_Event(event){}

	template <typename T, typename F>
	bool Dispatch(const F& func)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.Handle |= func(static_cast<T&>(m_Event));
			return true;
		}
		return false;
	}
private:
	SpoonEvent& m_Event;
};

inline std::ostream& operator<<(std::ostream& os, const SpoonEvent& e)
{
	return os << e.ToString();
}