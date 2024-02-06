#include "Widget.h"
#include "Renderer/DrawingInterfaceManager.h"

Widget::Widget() : 
    bIsAddedToViewport(false)
    , bIsEnabled(true)
    , visibility(Visibility::VISIBLE)
    , position(0, 0)
    , size(0, 0)
    , renderer(DrawingInterfaceManager::getInstance().getDrawingInterface())
{
}

void Widget::RemoveFromParent()
{ 
    if (parent.expired())
    {
		return;
	}

    auto parentPtr = parent.lock();
    parentPtr->RemoveChild(this);
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

void Widget::SetParent(std::shared_ptr<SObject> parent)
{
    this->parent = parent;
}

void Widget::SetPosition(FVector2D position)
{
	this->position = position;
}

void Widget::SetSize(FVector2D size)
{
	this->size = size;
}