#include "Widget.h"
#include "WidgetManager.h"
#include "Objects/SActor.h"

Widget::Widget() : 
    bIsAddedToViewport(false)
    , bIsTickable(false)
    , visibility(Visibility::VISIBLE)
    , parent(nullptr)
	, RelativePosition(0, 0)
    , worldPosition(0, 0)
	, Size(0, 0)
	, Rotation(0)
	, BaseStyle( { FColor(127, 127, 127, 50), FColor(255, 255, 255, 255), 2.f } )
	, HoverStyle( { FColor(127, 127, 127, 255), FColor(255, 255, 255, 255), 2.f } )
	, DisabledStyle( { FColor(127, 127, 127, 50), FColor(255, 0, 0, 255), 2.f } )
    , IsMarkedForDestruction(false)
    , bIsHovered(false)
    , bIsEnabled(true)
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
	worldPosition = RelativePosition;
	if (parent != nullptr)
	{
		SActor* parentActor = dynamic_cast<SActor*>(parent);

		if (parentActor)
		{
			worldPosition = parentActor->GetLocation() + RelativePosition;
			return;
		}

		Widget* parentWidget = dynamic_cast<Widget*>(parent);
		if (parentWidget)
		{
			worldPosition = parentWidget->worldPosition + RelativePosition;
		}
	}
}

bool Widget::IsPointInWidget(const FVector2D& mousePosition)
{
	if (mousePosition.X > worldPosition.X && mousePosition.X < worldPosition.X + Size.X &&
		mousePosition.Y > worldPosition.Y && mousePosition.Y < worldPosition.Y + Size.Y)
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

Style& Widget::GetStyle() const
{
	if (!bIsEnabled)
	{
		return const_cast<Style&>(DisabledStyle);
	}

	if (bIsHovered)
	{
		return const_cast<Style&>(HoverStyle);
	}

	return const_cast<Style&>(BaseStyle);
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