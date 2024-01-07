#include "Level.h"
#include "Objects/SActor.h"
#include "Library/Collision.h"
#include "Objects/Prefab/RectangleObject.h"
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
		}
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
			// TODO : Revoir ce code
			if (Collision::CheckCollisionImpl(dynamic_cast<SCircleObject*>(entity.get()), dynamic_cast<SCircleObject*>(obj)))
			{
				//std::cout << "Collision!!!!!" << std::endl;
			}
			else if (Collision::CheckCollisionImpl(dynamic_cast<SCircleObject*>(entity.get()), dynamic_cast<SRectangleObject*>(obj)))
			{

			}
			else if (Collision::CheckCollisionImpl(dynamic_cast<SRectangleObject*>(entity.get()), dynamic_cast<SCircleObject*>(obj)))
			{
				
			}
			else if (Collision::CheckCollisionImpl(dynamic_cast<SRectangleObject*>(entity.get()), dynamic_cast<SRectangleObject*>(obj)))
			{
				
			}
		}
	}
}