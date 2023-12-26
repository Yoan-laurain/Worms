#include <snpch.h>
#include "SActor.h"
#include "Spoon/Core/Level.h"

SActor::SActor() : 
	SObject(),
	ObjectColor(255, 255, 255, 255),
	WorldRef(nullptr)
{}

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


void SActor::SetColor(const FColor& color)
{
	ObjectColor = color;
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
