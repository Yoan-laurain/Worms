#include <snpch.h>
#include "SActor.h"
#include "Spoon/Core/Level.h"

SActor::SActor() :
	SObject(),
	WorldRef(nullptr),
	MyShape(nullptr)
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
{}

void SActor::DestroyActor()
{
	//GetWorld()->DestroyObject(this);
}

void SActor::SetWorldRef(Level* parentRef)
{
	WorldRef = parentRef;
}

void Shape::SetColor(const FColor& color)
{
	ObjectColor = color;
}