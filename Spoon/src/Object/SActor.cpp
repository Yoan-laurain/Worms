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
#ifdef DEBUG
	std::cout << "Perfect destroy" << std::endl;
#endif // DEBUG

}

void SActor::BeginPlay()
{
}

void SActor::Tick(float DeltaTime)
{}

void SActor::DestroyActor()
{
	//GetWorld()->DestroyObject(this);
}


void SActor::SetColor(const FColor& color)
{
	ObjectColor = color;
}


void SActor::SetWorldRef(Level* parentRef)
{
	WorldRef = parentRef;
}
