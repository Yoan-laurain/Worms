#include "Level.h"
#include "Objects/SActor.h"
#include "Library/Collision.h"
#include <snpch.h>

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

AlignAxisBoundingBox Level::GetAABB(SActor* obj)
{
	if (obj->bNeedToUpdateBoundingBox)
	{
		float minX = std::numeric_limits<float>::max();
		float minY = std::numeric_limits<float>::max();
		float maxX = std::numeric_limits<float>::min();
		float maxY = std::numeric_limits<float>::min();

		SPolygonObject* poly = dynamic_cast<SPolygonObject*>(obj);
		SCircleObject* circle = dynamic_cast<SCircleObject*>(obj);

		if ( poly )
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
		else if (circle)
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
	
	// TODO : Retrieve window size
	if (AABB.Max.X < 0 || AABB.Max.Y < 0 || AABB.Min.X > 1280 || AABB.Min.Y > 720)
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

void Level::HandleCollision(SActor* obj)
{
	for (const auto& entity : EntityList)
	{
		if (entity.get() != obj && entity.get() != nullptr)
		{
			if (Collision::CheckCollisionImpl(dynamic_cast<SCircleObject*>(entity.get()), dynamic_cast<SCircleObject*>(obj))) 
			{}
			else if (Collision::CheckCollisionImpl(dynamic_cast<SCircleObject*>(entity.get()), dynamic_cast<SPolygonObject*>(obj)))
			{}
			else if (Collision::CheckCollisionImpl(dynamic_cast<SPolygonObject*>(entity.get()), dynamic_cast<SCircleObject*>(obj)))
			{}
			else if (Collision::CheckCollisionImpl(dynamic_cast<SPolygonObject*>(entity.get()), dynamic_cast<SPolygonObject*>(obj)))
			{}
		}
	}
}