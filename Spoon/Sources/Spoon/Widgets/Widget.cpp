#include "Widget.h"
#include "Objects/SActor.h"

Widget::Widget() : 
    visibility(Visibility::VISIBLE)
    , Parent(nullptr)
    , RelativePosition(0, 0)
    , WorldPosition(0, 0)
	, Size(0, 0)
    , Rotation(0)
	, BaseStyle( { FColor(127, 127, 127, 50), FColor(255, 255, 255, 255), 2.f } )
	, HoverStyle( { FColor(127, 127, 127, 255), FColor(255, 255, 255, 255), 2.f } )
	, DisabledStyle( { FColor(127, 127, 127, 50), FColor(255, 0, 0, 255), 2.f } )
	, IsMarkedForDestruction(false)
	, bIsAddedToViewport(false)
    , bIsTickable(false)
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

void Widget::SetParent(SObject* Parent)
{
	this->Parent = Parent;
}

bool Widget::UpdateWorldPositionRelativeToParent()
{
	if (Parent != nullptr)
	{
		SActor* ParentActor = dynamic_cast<SActor*>(Parent);

		if (ParentActor)
		{
			WorldPosition = ParentActor->GetLocation() + RelativePosition;
			return true;
		}

		Widget* ParentWidget = dynamic_cast<Widget*>(Parent);
		if (ParentWidget)
		{
			WorldPosition = ParentWidget->WorldPosition + RelativePosition;
		}
	}
	return false;
}

void Widget::UpdateWorldPosition()
{
	WorldPosition = RelativePosition;
	
	UpdateWorldPositionRelativeToParent();
}

bool Widget::IsPointInWidget(const FVector2D& MousePosition)
{
	if (MousePosition.X > MousePosition.X && MousePosition.X < MousePosition.X + Size.X &&
		MousePosition.Y > MousePosition.Y && MousePosition.Y < MousePosition.Y + Size.Y)
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

void Widget::Tick(float DeltaTime)
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