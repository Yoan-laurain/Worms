#include "Level.h"
#include "Objects/SActor.h"
#include "Library/Collision.h"
#include "Application.h"
#include "Objects/Prefab/CircleObject.h"
#include <snpch.h>
#include <Widgets/WidgetManager.h>

Level::Level() : 
	bIsListBeingEdit(false),
	DebugShapes()
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

	for (const auto& entity : EntityList)
	{
		if (entity.get() != nullptr && entity.get()->bNeedToDestroy)
		{
			entity->DestroyActor();
		}
	}

	WidgetManager::GetInstance()->DestroyWidgetMarkedForDestruction(); 
}

void Level::ResolveCollision(Manifold& contact)
{
	SActor* bodyA = contact.BodyA;
	SActor* bodyB = contact.BodyB;
	const FVector2D normal = contact.Normal;

#if DEBUG

	DebugShapeData shape;
	shape.Shape = DebugShape::SPHERE;
	shape.Transform = FTransform(contact.Contact1, FVector2D(2.f, 2.f));

	AddDebugShape( shape );

	if (contact.ContactCount > 1)
	{
		shape.Transform = FTransform(contact.Contact2, FVector2D(2.f, 2.f));
		AddDebugShape( shape );
	}

#endif

	FVector2D relativeVelocity = bodyB->LinearVelocity - bodyA->LinearVelocity;

	if (FVector2D::DotProduct(relativeVelocity, normal) > 0.f) {
		return;
	}

	float e = fminf(bodyA->Restitution, bodyB->Restitution);

	float j = -(1.f + e) * (relativeVelocity.X * normal.X + relativeVelocity.Y * normal.Y);
	j /= bodyA->InvMass + bodyB->InvMass;

	FVector2D impulse = FVector2D(j * normal.X, j * normal.Y);

	bodyA->LinearVelocity -= impulse * bodyA->InvMass;
	bodyB->LinearVelocity += impulse * bodyB->InvMass;

	bodyA->OnCollide( bodyB );
	bodyB->OnCollide( bodyA );
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
	bIsListBeingEdit = true;
	AddEntityList.push_back(std::move(std::unique_ptr<SActor>(obj)));
	bIsListBeingEdit = false;
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

			if (entity.get())
			{
				AlignAxisBoundingBox& firstAABB = GetAABB(entity.get());
				AlignAxisBoundingBox& secondAABB = GetAABB(obj);

				// Dont bother checking for collision if the Axis Aligned Bounding Boxes dont overlap
				if (Collision::IntersectAABBs(firstAABB, secondAABB) == false)
				{
					continue;
				}

				NarrowPhase(entity.get(), obj);
			}
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