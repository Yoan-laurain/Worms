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
	, BackgroundColor(127,127,127,0)
	, parent(nullptr)
	, bIsHovered(false)
	, IsMarkedForDestruction(false)
	, bIsTickable(false)
	, rotation(0)
{
}

void Widget::RemoveFromParent()
{ 
    IsMarkedForDestruction = true;	
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

bool Widget::IsHovered() const
{
	return bIsHovered;
}

void Widget::OnHover()
{
	bIsHovered = true;
}

void Widget::OnUnhover()
{
	bIsHovered = false;
}

void Widget::Tick(float deltaTime)
{
}

void Widget::SetIsEnabled(bool bIsEnabled)
{
	this->bIsEnabled = bIsEnabled;

	if (!bIsEnabled)
	{
		bIsHovered = false;
	}
}

bool Widget::IsEnabled() const
{
	return bIsEnabled;
}