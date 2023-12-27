#include "SObject.h"
#include "Level.h"
#include "Object/Composant/CollisionShape.h"

SObject::SObject() : ObjectTransform(), bIsStatic(true)
{
	// todo remove this
	//CircleCollision* circle = new CircleCollision(ObjectTransform.Location,ObjectTransform.Size.X/2);
	//collisionShape = std::make_unique<CircleCollision>(circle);
}

SObject::~SObject()
{
}

FVector2D SObject::GetLocation() const
{
	return ObjectTransform.Location;
}

void SObject::SetLocation(const FVector2D& loc)
{
	std::mutex _mutex;
	_mutex.lock();
	ObjectTransform.Location = loc;
	_mutex.unlock();
}

FVector2D SObject::GetSize() const
{
	return ObjectTransform.Size;
}

void SObject::SetSize(const FVector2D& size)
{
	ObjectTransform.Size = size;
}

FTransform SObject::GetTransform() const
{
	return ObjectTransform;
}

void SObject::SetTransform(const FTransform& transform)
{
	ObjectTransform = transform;
}

bool SObject::IsInBound(const FVector2D& _loc) const
{
	FVector2D mintruc = GetLocation() - GetSize();
	if (_loc.X <= GetLocation().X && _loc.X >= mintruc.X && _loc.Y <= GetLocation().Y && _loc.Y >= mintruc.Y)
	{
#ifdef DEBUG
		std::cout << "Object coord : " << GetLocation() << " , curseur loc : " << _loc << std::endl;
#endif // DEBUG

		return true;
	}
	return false;
}

bool SObject::CheckCollision(const SObject& other) const
{
	return collisionShape.get()->CheckCollisionImpl(*other.collisionShape.get());
}

void SObject::OnCollide(const SObject& other)
{
	std::cout << " I'm colliding with " << std::endl;
}