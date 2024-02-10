#include "Widget.h"
#include "WidgetManager.h"
#include "Objects/SActor.h"

Widget::Widget() : 
    bIsAddedToViewport(false)
    , bIsEnabled(true)
    , visibility(Visibility::VISIBLE)
    , relativePosition(0, 0)
	, worldPosition(0, 0)
    , size(0, 0)
	, BackgroundColor(127,127,127,127)
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

void Widget::SetParent(SObject* parent)
{
	this->parent = parent;
}

void Widget::UpdateWorldPosition()
{
	worldPosition = relativePosition;
	if (parent != nullptr)
	{
		SActor* parentActor = dynamic_cast<SActor*>(parent);

		if (parentActor)
		{
			worldPosition = parentActor->GetLocation() + relativePosition;
			return;
		}

		Widget* parentWidget = dynamic_cast<Widget*>(parent);
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