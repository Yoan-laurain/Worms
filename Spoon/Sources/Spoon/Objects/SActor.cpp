#include "SActor.h"
#include "Core/Level.h"
#include "Events/MouseEvent.h"
#include "Components/SComponent.h"
#include <snpch.h>

SActor::SActor() :
	SObject(),
	WorldRef(nullptr),
	bIsHovered(false),
	bIsPressed(false)
{

	
	//std::unique_ptr<Rectangle> newShape = std::make_unique<Rectangle>();
	//newShape->height = GetSize().Y;
	//newShape->width = GetSize().X;
	//newShape->Type = FActorType::ActorType_Rectangle;
	//newShape->ObjectColor = FColor::White();
	//MyShape = std::move(newShape);
	//bIsStatic = false;

	//collisionShape = std::make_unique<CircleShape>(GetLocation(), 50);
}

SActor::~SActor()
{
	SetWorldRef(nullptr);

}

void SActor::BeginPlay()
{
}

void SActor::Tick(float DeltaTime)
{
	for (int i = 0; i < ComponentList.size(); ++i)
	{
		ComponentList[i]->OnUpdate(DeltaTime);
	}
	if (bIsPressed)
	{
		SetLocation(mouseLoc - (GetSize() / 2));
	}
}

void SActor::DestroyActor()
{
	GetWorld()->DestroyObject(this);
}

bool SActor::OnMouseEvent(MouseMovedEvent& _event)
{

	bIsHovered = IsInBound(_event.GetLoc());

	mouseLoc = (bIsPressed) ? _event.GetLoc() : GetLocation();

	return false;
}

bool SActor::OnMousePressedEvent(MouseButtonPressedEvent& _event)
{
	bIsPressed = bIsHovered;
	return bIsHovered;
}

bool SActor::OnMouseRelesedEvent(MouseButtonReleasedEvent& _event)
{
	bIsPressed = false;
	return false;
}

void SActor::OnEvent(SpoonEvent& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(SActor::OnMouseEvent));
	dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(SActor::OnMousePressedEvent));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(SActor::OnMouseRelesedEvent));
}

void SActor::SetWorldRef(Level* parentRef)
{
	WorldRef = parentRef;
}

FVector2D SActor::GetLocation() const
{
	return ObjectTransform.Location;
}

void SActor::SetLocation(const FVector2D& loc)
{
	std::unique_lock<std::mutex> _lock(_mutex);
	ObjectTransform.Location = loc;
}

FVector2D SActor::GetSize() const
{
	return ObjectTransform.Size;
}

void SActor::SetSize(const FVector2D& size)
{
	std::unique_lock<std::mutex> _lock(_mutex);
	ObjectTransform.Size = size;
}

FTransform SActor::GetTransform() const
{
	return ObjectTransform;
}

void SActor::SetTransform(const FTransform& transform)
{
	std::unique_lock<std::mutex> _lock(_mutex);
	ObjectTransform = transform;
}

bool SActor::IsInBound(const FVector2D& _loc) const
{
	FVector2D mintruc = GetLocation() + GetSize();
	if (_loc.X >= GetLocation().X && _loc.X <= mintruc.X && _loc.Y >= GetLocation().Y && _loc.Y <= mintruc.Y)
	{
#ifdef DEBUG
		// std::cout << "Object coord : " << GetLocation() << " , curseur loc : " << _loc << std::endl;
#endif // DEBUG
		return true;
	}
	return false;
}
