#include "Level.h"
#include "Objects/SActor.h"
#include "Library/Collision.h"
#include "Application.h"
#include "Objects/Prefab/CircleObject.h"
#include <snpch.h>

Level::Level() : 
	bIsListBeingEdit(false),
	DebugShapes(),
	rbList(2),
	raList(2),
	impulseList(2),
	contactList(2),
	frictionImpulseList(2),
	jList(2)
{
}

Level::~Level()
{}

void Level::UpdateEntity(double deltatime)
{
	if (!AddEntityList.empty())
	{
		bIsListBeingEdit = true;
		for (unsigned int i = 0; i < AddEntityList.size(); ++i)
		{
			if (AddEntityList[i].get() != nullptr)
			{
				AddEntityList[i]->BeginPlay();
				EntityList.push_back(std::move(AddEntityList[i]));
			}
		}
		AddEntityList.clear();
		bIsListBeingEdit = false;
	}

	for (const auto& entity : EntityList)
	{
		if (entity.get() != nullptr)
		{
			entity->Tick(deltatime);

			if (!entity->bIsStatic)
			{
				HandleCollision(entity.get());
			}

			HandleObjectOutOfWindow(entity.get());
		}
	}
}

void Level::ResolveCollision(Manifold& contact)
{
	SActor& bodyA = *contact.BodyA;
	SActor& bodyB = *contact.BodyB;
	const FVector2D& normal = contact.Normal;
	const FVector2D& contact1 = contact.Contact1;
	const FVector2D& contact2 = contact.Contact2;
	int contactCount = contact.ContactCount;

#if DEBUG

	DebugShapeData shape;
	shape.Shape = DebugShape::SPHERE;
	shape.Transform = FTransform(contact.Contact1, FVector2D(2.f, 2.f));

	AddDebugShape(shape);

	if (contact.ContactCount > 1)
	{
		shape.Transform = FTransform(contact.Contact2, FVector2D(2.f, 2.f));
		AddDebugShape(shape);
	}

#endif

	float e = std::min(bodyA.Restitution, bodyB.Restitution);

	contactList[0] = contact1;
	contactList[1] = contact2;

	for (int i = 0; i < contactCount; ++i)
	{
		impulseList[i] = FVector2D::Zero();
		raList[i] = FVector2D::Zero();
		rbList[i] = FVector2D::Zero();
		frictionImpulseList[i] = FVector2D::Zero();
		jList[i] = 0.f;
	}

	for (int i = 0; i < contactCount; ++i)
	{
		FVector2D ra = contactList[i] - bodyA.GetLocation();
		FVector2D rb = contactList[i] - bodyB.GetLocation();

		raList[i] = ra;
		rbList[i] = rb;

		FVector2D raPerp(-ra.Y, ra.X);
		FVector2D rbPerp(-rb.Y, rb.X);

		//FVector2D angularLinearVelocityA = raPerp * bodyA.AngularVelocity;
		//FVector2D angularLinearVelocityB = rbPerp * bodyB.AngularVelocity;

		FVector2D relativeVelocity =
			(bodyB.LinearVelocity) -
			(bodyA.LinearVelocity );

		float contactVelocityMag = FVector2D::DotProduct(relativeVelocity, normal);

		if (contactVelocityMag > 0.0f)
		{
			continue;
		}

		float raPerpDotN = FVector2D::DotProduct(raPerp, normal);
		float rbPerpDotN = FVector2D::DotProduct(rbPerp, normal);

		float denom = bodyA.InvMass + bodyB.InvMass +
			(raPerpDotN * raPerpDotN) * bodyA.InvInertia +
			(rbPerpDotN * rbPerpDotN) * bodyB.InvInertia;

		float j = -(1.0f + e) * contactVelocityMag;
		j /= denom;
		j /= static_cast<float>(contactCount);

		jList[i] = j;

		FVector2D impulse = normal * j;
		impulseList[i] = impulse;
	}

	FVector2D relativeVelocity = bodyB.LinearVelocity - bodyA.LinearVelocity;

	if (FVector2D::DotProduct(relativeVelocity, normal) < 0.f) {
		float j = -(1.f + e) * (relativeVelocity.X * normal.X + relativeVelocity.Y * normal.Y);
		j /= bodyA.InvMass + bodyB.InvMass;

		FVector2D impulse = FVector2D(j * normal.X, j * normal.Y);

		bodyA.LinearVelocity -= impulse * bodyA.InvMass;
		bodyB.LinearVelocity += impulse * bodyB.InvMass;
	}


	ApplyFriction(contact);
}

void Level::ApplyFriction(Manifold& contact)
{
	float sf = (contact.BodyA->StaticFriction + contact.BodyB->StaticFriction) * 0.5f;
	float df = (contact.BodyA->DynamicFriction + contact.BodyB->DynamicFriction) * 0.5f;

	for (int i = 0; i < contact.ContactCount; i++) {
		FVector2D ra = contactList[i] - contact.BodyA->GetLocation();
		FVector2D rb = contactList[i] - contact.BodyB->GetLocation();

		raList[i] = ra;
		rbList[i] = rb;

		FVector2D raPerp(-ra.Y, ra.X);
		FVector2D rbPerp(-rb.Y, rb.X);

		FVector2D angularLinearVelocityA = raPerp * contact.BodyA->AngularVelocity;
		FVector2D angularLinearVelocityB = rbPerp * contact.BodyB->AngularVelocity;

		FVector2D relativeVelocity =
			(contact.BodyB->LinearVelocity + angularLinearVelocityB) -
			(contact.BodyA->LinearVelocity + angularLinearVelocityA);

		FVector2D tangent = relativeVelocity - FVector2D::DotProduct(relativeVelocity, contact.Normal) * contact.Normal;

		if (FVector2D::NearlyEqual(tangent, FVector2D::Zero())) {
			continue;
		}
		else {
			tangent = FVector2D::Normalize(tangent);
		}

		float raPerpDotT = FVector2D::DotProduct(raPerp, tangent);
		float rbPerpDotT = FVector2D::DotProduct(rbPerp, tangent);

		float denom = contact.BodyA->InvMass + contact.BodyB->InvMass +
			(raPerpDotT * raPerpDotT) * contact.BodyA->InvInertia +
			(rbPerpDotT * rbPerpDotT) * contact.BodyB->InvInertia;

		float jt = -FVector2D::DotProduct(relativeVelocity, tangent);
		jt /= denom;
		jt /= static_cast<float>(contact.ContactCount);

		FVector2D frictionImpulse;
		float j = jList[i];

		if (std::abs(jt) <= j * sf) {
			frictionImpulse = tangent * jt;
		}
		else {
			frictionImpulse = tangent * df * -j;
		}

		frictionImpulseList[i] = frictionImpulse;
	}

	for (int i = 0; i < contact.ContactCount; i++) {
		FVector2D frictionImpulse = frictionImpulseList[i];
		FVector2D ra = raList[i];
		FVector2D rb = rbList[i];

		std::cout << "Friction impulse: " << frictionImpulse.X << ", " << frictionImpulse.Y << std::endl;

		FVector2D res = frictionImpulse.ReverseVector() * contact.BodyA->InvMass;

		contact.BodyA->LinearVelocity += res ;
		//contact.BodyA->AngularVelocity += -FVector2D::Cross(ra, frictionImpulse) * contact.BodyA->InvInertia;
		contact.BodyB->LinearVelocity += frictionImpulse * contact.BodyB->InvMass;
		//contact.BodyB->AngularVelocity += FVector2D::Cross(rb, frictionImpulse) * contact.BodyB->InvInertia;
	}
}

AlignAxisBoundingBox& Level::GetAABB(SActor* obj)
{
	if (obj->bNeedToUpdateBoundingBox)
	{
		float minX = std::numeric_limits<float>::max();
		float minY = std::numeric_limits<float>::max();
		float maxX = std::numeric_limits<float>::min();
		float maxY = std::numeric_limits<float>::min();

		if (SPolygonObject* poly = dynamic_cast<SPolygonObject*>(obj))
		{
			std::vector<FVector2D> vertices = poly->GetVertices();

			for (const auto& v : vertices)
			{
				if (v.X < minX) { minX = v.X; }
				if (v.X > maxX) { maxX = v.X; }
				if (v.Y < minY) { minY = v.Y; }
				if (v.Y > maxY) { maxY = v.Y; }
			}
		}
		else if (SCircleObject* circle = dynamic_cast<SCircleObject*>(obj))
		{
			minX = circle->GetLocation().X - circle->GetRadius();
			minY = circle->GetLocation().Y - circle->GetRadius();
			maxX = circle->GetLocation().X + circle->GetRadius();
			maxY = circle->GetLocation().Y + circle->GetRadius();
		}
		else
		{
			throw std::runtime_error("Unknown ShapeType.");
		}

		obj->AABB = AlignAxisBoundingBox(minX, minY, maxX, maxY);
	}

	obj->bNeedToUpdateBoundingBox = false;
	return obj->AABB;
}

void Level::HandleObjectOutOfWindow(SActor* obj)
{
	AlignAxisBoundingBox AABB = GetAABB(obj);

	if (AABB.Max.X < 0 || AABB.Max.Y < 0 || AABB.Min.X > Application::Get().GetScreenSize().X || AABB.Min.Y > Application::Get().GetScreenSize().Y)
	{
		obj->DestroyActor();
	}
}

void Level::DestroyObject(class SActor* _actor)
{
	RemoveObject(_actor);
}

void Level::RemoveObject(SActor* obj)
{
	auto it = std::remove_if(EntityList.begin(), EntityList.end(), [obj](std::unique_ptr<SActor>& ptr) {
		if (ptr->GetUniqueId() == obj->GetUniqueId())
		{
			ptr.reset();
			return true;
		}
		return false;
	});

	EntityList.erase(it, EntityList.end());
}

void Level::AddObject(SActor* obj)
{
	if (!obj)
	{
		std::cout << "Add objet null" <<  std::endl;
		return;
	}
	auto tmp = std::remove_if(EntityList.begin(), EntityList.end(), [obj](const std::unique_ptr<SActor>& ptr) { return ptr->GetUniqueId() == obj->GetUniqueId(); });
	if (tmp != EntityList.end())
	{
		std::cout << "Objet already in the list" << std::endl;
		return;
	}

	AddEntityList.push_back(std::move(std::unique_ptr<SActor>(obj)));
}

void Level::AddDebugShape(const DebugShapeData& shape)
{
	std::unique_lock<std::mutex> lock(_mutex);
	
	for (const auto& s : DebugShapes)
	{
		if (FVector2D::NearlyEqual(s.Transform.Location , shape.Transform.Location, 0.1f))
		{
			return;
		}
	}	

	DebugShapes.push_back(shape);
}

void Level::ClearDebugShapes()
{
	std::unique_lock<std::mutex> lock(_mutex);

	DebugShapes.clear();
}

int Level::GetEntityCount() const
{
	return EntityList.size();
}

void Level::HandleCollision( SActor* obj )
{
	for (const auto& entity : EntityList)
	{
		if (entity.get() != obj && entity.get() != nullptr)
		{
			if (entity->bIsStatic && obj->bIsStatic)
			{
				continue;
			}

			AlignAxisBoundingBox& firstAABB = GetAABB(entity.get());
			AlignAxisBoundingBox& secondAABB = GetAABB(obj);

			// Dont bother checking for collision if the Axis Aligned Bounding Boxes dont overlap
			if (Collision::IntersectAABBs(firstAABB, secondAABB) == false)
			{
				continue;
			}

			NarrowPhase( entity.get(), obj );
		}
	}
}

void Level::NarrowPhase(SActor* entity, SActor* obj)
{
	Manifold collision;

	if (Collision::CheckCollisionImpl(dynamic_cast<SCircleObject*>(entity), dynamic_cast<SCircleObject*>(obj), collision))
	{
		ResolveCollision(collision);
	}
	else if (Collision::CheckCollisionImpl(dynamic_cast<SCircleObject*>(entity), dynamic_cast<SPolygonObject*>(obj), collision))
	{
		ResolveCollision(collision);
	}
	else if (Collision::CheckCollisionImpl(dynamic_cast<SPolygonObject*>(entity), dynamic_cast<SCircleObject*>(obj), collision))
	{
		ResolveCollision(collision);
	}
	else if (Collision::CheckCollisionImpl(dynamic_cast<SPolygonObject*>(entity), dynamic_cast<SPolygonObject*>(obj), collision))
	{
		ResolveCollision(collision);
	}
}