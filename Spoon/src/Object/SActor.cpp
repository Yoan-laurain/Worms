#include "SActor.h"
#include "Spoon/Core/Level.h"
#include "Spoon/Events/MouseEvent.h"
#include "Component/SComponent.h"
#include <snpch.h>

SActor::SActor() :
	SObject(),
	WorldRef(nullptr),
	MyShape(nullptr),
	bIsHovered(false),
	bIsPressed(false)
{
	Rectangle* newShape = new Rectangle();
	newShape->height = GetSize().Y;
	newShape->width = GetSize().X;
	newShape->Type = FActorType::ActorType_Rectangle;
	newShape->ObjectColor = FColor::White();

	MyShape = newShape;

	bIsStatic = false;
}

SActor::~SActor()
{
	SetWorldRef(nullptr);
#ifdef DEBUG
	std::cout << "Perfect destroy" << std::endl;
#endif // DEBUG

}

void SActor::BeginPlay()
{
}

void SActor::Tick(float DeltaTime)
{
	for (int i = 0; i < ComposanList.size(); ++i)
	{
		ComposanList[i]->OnUpdate(DeltaTime);
	}
	if (bIsPressed)
	{
		SetLocation(mouseLoc - (GetSize() / 2));
	}
}

void SActor::DestroyActor()
{
	//GetWorld()->DestroyObject(this);
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

void Shape::SetColor(const FColor& color)
{
	ObjectColor = color;
}