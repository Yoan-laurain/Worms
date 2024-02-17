#include "Level.h"
#include "Objects/SActor.h"
#include "Library/Collision.h"
#include "Application.h"
#include "Objects/Prefab/CircleObject.h"
#include <snpch.h>
#include <Widgets/WidgetManager.h>

Level::Level() : 
	bIsListBeingEdit(false)
{
}

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

void Level::ResolveCollision(const Manifold& Contact)
{
	SActor* BodyA = Contact.BodyA;
	SActor* BodyB = Contact.BodyB;
	const FVector2D Normal = Contact.Normal;

#if DEBUG

	DebugShapeData shape;
	shape.Shape = SPHERE;
	shape.Transform = FTransform(Contact.Contact1, FVector2D(2.f, 2.f));

	AddDebugShape( shape );

	if (Contact.ContactCount > 1)
	{
		shape.Transform = FTransform(Contact.Contact2, FVector2D(2.f, 2.f));
		AddDebugShape( shape );
	}

#endif

	BodyA->OnCollide(BodyB);
	BodyB->OnCollide(BodyA);

	const FVector2D RelativeVelocity = BodyB->LinearVelocity - BodyA->LinearVelocity;

	if (FVector2D::DotProduct(RelativeVelocity, Normal) > 0.f)
		return;

	const float E = fminf(BodyA->Restitution, BodyB->Restitution);

	float j = -(1.f + E) * (RelativeVelocity.X * Normal.X + RelativeVelocity.Y * Normal.Y);
	j /= BodyA->InvMass + BodyB->InvMass;

	const FVector2D Impulse = FVector2D(j * Normal.X, j * Normal.Y);

	BodyA->LinearVelocity -= Impulse * BodyA->InvMass;
	BodyB->LinearVelocity += Impulse * BodyB->InvMass;
}

AlignAxisBoundingBox& Level::GetAABB(SActor* Obj)
{
	if (Obj->bNeedToUpdateBoundingBox)
	{
		float MinX = std::numeric_limits<float>::max();
		float MinY = std::numeric_limits<float>::max();
		float MaxX = std::numeric_limits<float>::min();
		float MaxY = std::numeric_limits<float>::min();

		if (SPolygonObject* Poly = dynamic_cast<SPolygonObject*>(Obj))
		{
			const std::vector<FVector2D>& Vertices = Poly->GetVertices();

			for (const auto& V : Vertices)
			{
				if (V.X < MinX) { MinX = V.X; }
				if (V.X > MaxX) { MaxX = V.X; }
				if (V.Y < MinY) { MinY = V.Y; }
				if (V.Y > MaxY) { MaxY = V.Y; }
			}
		}
		else if (SCircleObject* Circle = dynamic_cast<SCircleObject*>(Obj))
		{
			MinX = Circle->GetLocation().X - Circle->GetRadius();
			MinY = Circle->GetLocation().Y - Circle->GetRadius();
			MaxX = Circle->GetLocation().X + Circle->GetRadius();
			MaxY = Circle->GetLocation().Y + Circle->GetRadius();
		}
		else
		{
			throw std::runtime_error("Unknown ShapeType.");
		}

		Obj->AABB = AlignAxisBoundingBox(MinX, MinY, MaxX, MaxY);
	}

	Obj->bNeedToUpdateBoundingBox = false;
	return Obj->AABB;
}

void Level::HandleObjectOutOfWindow(SActor* Obj)
{
	const AlignAxisBoundingBox& AABB = GetAABB(Obj);

	if (AABB.Max.X < 0 || AABB.Max.Y < 0 || AABB.Min.X > Application::Get().GetScreenSize().X || AABB.Min.Y > Application::Get().GetScreenSize().Y)
	{
		Obj->DestroyActor();
	}
}

void Level::DestroyObject(SActor* _actor)
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

#if DEBUG
void Level::AddDebugShape(const DebugShapeData& Shape)
{
	std::unique_lock lock(_mutex);
	
	for (const auto& S : DebugShapes)
	{
		if (FVector2D::NearlyEqual(S.Transform.Location , Shape.Transform.Location, 0.1f))
		{
			return;
		}
	}	

	DebugShapes.push_back(Shape);
}

void Level::ClearDebugShapes()
{
	std::unique_lock lock(_mutex);

	DebugShapes.clear();
}
#endif

int Level::GetEntityCount() const
{
	return EntityList.size();
}

void Level::HandleCollision( SActor* Obj )
{
	for (const auto& Entity : EntityList)
	{
		if (Entity.get() != Obj && Entity.get() != nullptr)
		{
			if (Entity->bIsStatic && Obj->bIsStatic)
			{
				continue;
			}

			if (Entity.get())
			{
				AlignAxisBoundingBox& FirstAABB = GetAABB(Entity.get());
				AlignAxisBoundingBox& SecondAABB = GetAABB(Obj);

				// Dont bother checking for collision if the Axis Aligned Bounding Boxes dont overlap
				if (Collision::IntersectAABBs(FirstAABB, SecondAABB) == false)
				{
					continue;
				}

				NarrowPhase(Entity.get(), Obj);
			}
		}
	}
}

void Level::NarrowPhase(SActor* Entity, SActor* Obj)
{
	Manifold Collision;

	if (Collision::CheckCollisionImpl(dynamic_cast<SCircleObject*>(Entity), dynamic_cast<SCircleObject*>(Obj), Collision))
	{
		ResolveCollision(Collision); 
	}
	else if (Collision::CheckCollisionImpl(dynamic_cast<SCircleObject*>(Entity), dynamic_cast<SPolygonObject*>(Obj), Collision))
	{
		ResolveCollision(Collision); 
	}
	else if (Collision::CheckCollisionImpl(dynamic_cast<SPolygonObject*>(Entity), dynamic_cast<SCircleObject*>(Obj), Collision))
	{
		ResolveCollision(Collision);
	}
	else if (Collision::CheckCollisionImpl(dynamic_cast<SPolygonObject*>(Entity), dynamic_cast<SPolygonObject*>(Obj), Collision))
	{
		ResolveCollision(Collision);
	}
}