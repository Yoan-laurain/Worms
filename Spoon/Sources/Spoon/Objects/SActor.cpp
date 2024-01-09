#include "SActor.h"
#include "Core/Level.h"
#include "Events/MouseEvent.h"
#include "Components/SComponent.h"
#include "Library/MathLibrary.h"
#include <snpch.h>

SActor::SActor() :
	SObject(),
	WorldRef(nullptr),
	bIsHovered(false),
	bIsPressed(false),
	bIsStatic(false),
	Mass(1.f),
	LinearVelocity(FVector2D::Zero()),
	Restitution(0.5f),
	InvMass(1.f / Mass),
	Force(FVector2D::Zero()),
	bIsColliding(false),
	RotationalVelocity(0.f),
	Magnitude(8.f),
	Gravity(FVector2D(0.f, MathLibrary::Gravity)),
	AABB(FVector2D::Zero(), FVector2D::Zero()),
	bNeedToUpdateBoundingBox(true)
{
	if (bIsStatic)
	{
		InvMass = 0.f;
	}
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
	if (bIsPressed && bIsHovered)
	{
		if (!bIsStatic)
		{
			SetLocation(mouseLoc);
		}
	}

	Step(DeltaTime);
}

void SActor::DestroyActor()
{
	GetWorld()->DestroyObject(this);
}

bool SActor::OnMouseEvent(MouseMovedEvent& _event)
{
	if (bIsPressed)
	{
		bIsHovered = IsInBound(_event.GetLoc());
	}
	else
	{
		bIsHovered = false;
	}

	mouseLoc = (bIsPressed) ? _event.GetLoc() : GetLocation();

	return false;
}

bool SActor::OnMousePressedEvent(MouseButtonPressedEvent& _event)
{
	bIsPressed = true;
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

void SActor::Step(float DeltaTime)
{
	if (bIsStatic)
	{
		return;
	}

	// TODO : Get a list of forces
	LinearVelocity += (Gravity + Force) * DeltaTime;

	if (LinearVelocity != FVector2D::Zero())
	{
		bNeedToUpdateBoundingBox = true;
	}

	ObjectTransform.Location += LinearVelocity * DeltaTime;
	ObjectTransform.Rotation += RotationalVelocity * DeltaTime;
	Force = FVector2D::Zero();
}

void SActor::AddForce(const FVector2D& force)
{
	Force = force;
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

void SActor::Move(const FVector2D& loc)
{
	if (!bIsStatic)
	{
		std::unique_lock<std::mutex> _lock(_mutex);
		ObjectTransform.Location += loc;
	}
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

bool SActor::IsInBound(const FVector2D& _loc)
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
