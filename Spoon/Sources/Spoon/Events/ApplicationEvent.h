#pragma once
#include "SpoonEvent.h"

class WindowResizeEvent : public SpoonEvent
{
public:
	WindowResizeEvent(unsigned int width, unsigned int height)
		: m_Width(width), m_Height(height) {}

	unsigned int GetWidth() const { return m_Width; }
	unsigned int GetHeight() const { return m_Height; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
private:
	unsigned int m_Width, m_Height;
};

class WindowCloseEvent : public SpoonEvent
{
public:
	WindowCloseEvent() = default;

	EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppTickEvent : public SpoonEvent
{
public:
	AppTickEvent(float deltatime) :DeltaTime(deltatime) {};

	float GetDeltaTime() const { return DeltaTime; }

	EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
private:
	float DeltaTime;
};

class AppUpdateEvent : public SpoonEvent
{
public:
	AppUpdateEvent() = default;

	EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppRenderEvent : public SpoonEvent
{
public:
	AppRenderEvent() = default;

	EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
};