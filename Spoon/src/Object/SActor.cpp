#include <snpch.h>
#include "SActor.h"
#include "Spoon/Core/Level.h"

SActor::SActor() : 
	SObject(),
	WorldRef(nullptr),
	MyShape(nullptr),
	Render(nullptr)
{
	Rectangle* newShape = new Rectangle();
	newShape->height = GetSize().Y;
	newShape->width = GetSize().X;
	newShape->Type = FActorType::ActorType_Rectangle;
	newShape->ObjectColor = FColor::White();

	MyShape = newShape;
}

SActor::~SActor()
{
	SetWorldRef(nullptr);
}

void SActor::BeginPlay()
{
}

void SActor::Tick(float DeltaTime)
{}

void SActor::DestroyActor()
{
	delete this;
}

void SActor::SetWorldRef(Level* parentRef)
{
	if (WorldRef)
	{
		WorldRef->RemoveObject(this);
	}
	WorldRef = parentRef;
	if (WorldRef)
	{
		WorldRef->AddObject(this);
	}
}

void Shape::SetColor(const FColor& color)
{
	ObjectColor = color;
}