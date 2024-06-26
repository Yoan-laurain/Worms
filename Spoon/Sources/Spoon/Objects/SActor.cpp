#include "SActor.h"
#include "Core/Level.h"
#include "Events/MouseEvent.h"
#include "Components/SComponent.h"
#include "Library/MathLibrary.h"
#include <snpch.h>

SActor::SActor() :
	bIsStatic(false),
	bIsColliding(false),
	LinearVelocity(FVector2D::Zero()),
	RotationalVelocity(0.f),
	Restitution(0.5f),
	Magnitude(8.f),
	Density(1.f),
	bNeedToUpdateBoundingBox(true),
	AABB(FVector2D::Zero(), FVector2D::Zero()),
	LifeSpan(-1.f),
	bNeedToDestroy(false),
	WorldRef(nullptr),
	Mass(1.f),
	InvMass(1.f / Mass),
	Force(FVector2D::Zero()),
	Gravity(FVector2D(0.f, MathLibrary::Gravity))
{
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
	if (LifeSpan != -1)
	{
		LifeSpan -= DeltaTime;

		if (LifeSpan <= 0.f)
		{
			DestroyActor();
		}
	}

	for (auto& i : ComponentList)
	{
		i->OnUpdate(DeltaTime);
	}

	UpdateObjectPhysics(DeltaTime);
}

void SActor::MarkActorToDestruction()
{
	bNeedToDestroy = true;
}

void SActor::DestroyActor()
{
	GetWorld()->DestroyObject(this);
}

void SActor::OnEvent(SpoonEvent& event)
{
	EventDispatcher dispatcher(event);
}

void SActor::SetWorldRef(Level* parentRef)
{
	WorldRef = parentRef;
}

void SActor::ClampAcceleration()
{
	if ( Force != FVector2D::Zero()) // We clamp the velocity to the max velocity if needed
	{
		FVector2D MaxVelocity = Gravity + Force;

		MaxVelocity = FVector2D(MathLibrary::Abs(MaxVelocity.X), MathLibrary::Abs(MaxVelocity.Y));	
	
		LinearVelocity.X = MathLibrary::Clamp(LinearVelocity.X, -MaxVelocity.X , MaxVelocity.X);
		LinearVelocity.Y = MathLibrary::Clamp(LinearVelocity.Y, -MaxVelocity.Y, MaxVelocity.Y);
	}
}

void SActor::UpdateObjectPhysics(float DeltaTime)
{
	if (bIsStatic)
	{
		return;
	}

	LinearVelocity += Gravity * DeltaTime + Force;

	ClampAcceleration();
	
	if (LinearVelocity != FVector2D::Zero())
	{
		bNeedToUpdateBoundingBox = true;
	}

	ObjectTransform.Location += LinearVelocity * DeltaTime;
	ObjectTransform.Rotation += RotationalVelocity * DeltaTime;
	Force = FVector2D::Zero();
}

void SActor::AddForce(const FVector2D& Force)
{
	this->Force = Force;
}

float SActor::GetMass() const
{
	return Mass;
}

void SActor::SetDensity(float Density)
{
	this->Density = Density;
	UpdateMass();
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

// TODO Does not work since the rotation is not implemented
FVector2D SActor::GetForwardVector() const
{
	FVector2D direction = FVector2D(cosf(ObjectTransform.Rotation), sinf(ObjectTransform.Rotation));
	return direction.GetSafeNormal();
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

	UpdateMass();
}

void SActor::UpdateMass()
{
	if (bIsStatic)
	{
		return;
	}

	Mass = Density * ObjectTransform.Size.X * ObjectTransform.Size.Y;
	InvMass = bIsStatic ? 0.f : 1.f / Mass;
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

void SActor::OnCollide(SObject* Actor)
{

}