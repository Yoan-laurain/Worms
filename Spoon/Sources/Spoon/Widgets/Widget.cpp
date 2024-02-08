#include "Widget.h"
#include "Renderer/DrawingInterfaceManager.h"
#include "WidgetManager.h"
#include <Objects/SActor.h>

Widget::Widget() : 
    bIsAddedToViewport(false)
    , bIsEnabled(true)
    , visibility(Visibility::VISIBLE)
    , relativePosition(0, 0)
	, worldPosition(0, 0)
    , size(0, 0)
    , renderer(DrawingInterfaceManager::getInstance().getDrawingInterface())
{
}

void Widget::RemoveFromParent()
{ 
    if (parent == nullptr)
	{
		return;
	}

    WidgetManager::GetInstance()->RemoveWidget(this);
}

void Widget::AddToViewport()
{
    bIsAddedToViewport = true;
}

void Widget::SetIsEnabled(bool bIsEnabled)
{
    this->bIsEnabled = bIsEnabled;
}

void Widget::SetVisibility(Visibility visibility)
{
    this->visibility = visibility;
}

void Widget::SetParent(std::unique_ptr<SObject> parent)
{
    this->parent = std::move(parent);   
}

void Widget::SetRelativePosition(FVector2D position)
{
	this->relativePosition = position;
}

void Widget::SetSize(FVector2D size)
{
	this->size = size;
}

void Widget::UpdateWorldPosition()
{
	worldPosition = relativePosition;
	if (parent.get())
	{
		SActor* parentActor = dynamic_cast<SActor*>(parent.get());

		if (parentActor)
		{
			worldPosition = parentActor->GetLocation() + relativePosition;
			return;
		}

		Widget* parentWidget = dynamic_cast<Widget*>(parent.get());
		if (parentWidget)
		{
			worldPosition = parentWidget->worldPosition + relativePosition;
		}
	}
}

bool Widget::IsPointInWidget(const FVector2D& mousePosition)
{
	if (mousePosition.X > worldPosition.X && mousePosition.X < worldPosition.X + size.X &&
		mousePosition.Y > worldPosition.Y && mousePosition.Y < worldPosition.Y + size.Y)
	{
		return true;
	}
	return false;
}
