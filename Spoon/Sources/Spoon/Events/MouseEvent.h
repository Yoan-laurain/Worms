#pragma once

#include "SpoonEvent.h"
#include "Inputs/MouseCode.h"

class MouseMovedEvent : public SpoonEvent
{
public:
	MouseMovedEvent(const FVector2D& _loc)
		: m_MouseLoc(_loc) {}

	float GetX() const { return m_MouseLoc.X; }
	float GetY() const { return m_MouseLoc.Y; }

	FVector2D GetLoc() const { return m_MouseLoc; }

	EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
	FVector2D m_MouseLoc;
};

class MouseScrolledEvent : public SpoonEvent
{
public:
	MouseScrolledEvent(const float xOffset, const float yOffset)
		: m_XOffset(xOffset), m_YOffset(yOffset) {}

	float GetXOffset() const { return m_XOffset; }
	float GetYOffset() const { return m_YOffset; }

	EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
	float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public SpoonEvent
{
public:
	MouseCode GetMouseButton() const { return m_Button; }

	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
protected:
	MouseButtonEvent(const MouseCode button)
		: m_Button(button) {}

	MouseCode m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(const MouseCode button)
		: MouseButtonEvent(button) {}

	EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(const MouseCode button)
		: MouseButtonEvent(button) {}

	EVENT_CLASS_TYPE(MouseButtonReleased)
};

