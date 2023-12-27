#include "snpch.h"
#include "Level.h"
#include "SObject.h"

Level::~Level()
{
	auto ListObj = AddEntityList;
	for (auto obj : ListObj)
	{
		obj->DestroyActor();
	}
	auto ListObject = EntityList;
	for (auto object : ListObject)
	{
		object->DestroyActor();
	}
}

void Level::UpdateEntity(double deltatime)
{
	if (!AddEntityList.empty())
	{
		bIsListBeingEdit = true;
		auto tmpAddList = AddEntityList;
		for (SActor* addEntity : tmpAddList)
		{
			if (addEntity != nullptr)
			{
				EntityList.push_back(addEntity);
				addEntity->BeginPlay();
			}
		}
		AddEntityList.clear();
		bIsListBeingEdit = false;
	}
	for (SActor* entity : EntityList)
	{
		if (entity != nullptr)
		{
			entity->Tick(deltatime);

			if (!entity->bIsStatic)
			{
				 HandleCollision(entity);
			}
		}

	}
}

void Level::RemoveObject(SActor* obj)
{
	auto tmp = std::find(EntityList.begin(), EntityList.end(), obj);
	if (tmp == EntityList.end())
	{
		std::cout << "Objet non trouver dans la list objets" << std::endl;
		return;
	}
	EntityList.erase(tmp);
}

void Level::AddObject(SActor* obj)
{
	if (!obj)
	{
		std::cout << "Add objet null" <<  std::endl;
		return;
	}
	auto tmp = std::find(EntityList.begin(), EntityList.end(), obj);
	if (tmp != EntityList.end())
	{
		std::cout << "Objet already in the list" << std::endl;
		return;
	}
	AddEntityList.push_back(obj);
}

void Level::HandleCollision(SActor* obj)
{
	for (SActor* entity : EntityList)
	{
		if (entity != nullptr && entity != obj)
		{
			entity->CheckCollision(*obj);
		}
	}
}