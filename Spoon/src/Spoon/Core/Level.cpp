#include "Level.h"
#include "Object/SActor.h"
#include "Object/Composant/CollisionShape.h"
#include <snpch.h>

Level::~Level()
{}

void Level::UpdateEntity(double deltatime)
{
	if (!AddEntityList.empty())
	{
		bIsListBeingEdit = true;
		auto tmpAddList = AddEntityList;
		for (std::shared_ptr<SActor> addEntity : tmpAddList)
		{
			if (addEntity.get() != nullptr)
			{
				EntityList.push_back(addEntity);
				addEntity->BeginPlay();
			}
		}
		AddEntityList.clear();
		bIsListBeingEdit = false;
	}
	for (std::shared_ptr<SActor> entity : EntityList)
	{
		if (entity != nullptr)
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
	RemoveObject(std::shared_ptr<SActor>(_actor));
}

void Level::RemoveObject(std::shared_ptr<SActor> obj)
{
	auto tmp = std::find(EntityList.begin(), EntityList.end(), obj);
	if (tmp == EntityList.end())
	{
		std::cout << "Objet non trouver dans la list objets" << std::endl;
		return;
	}
	EntityList.erase(tmp);
}

void Level::AddObject(std::shared_ptr<SActor> obj)
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
	for (std::shared_ptr<SActor> entity : EntityList)
	{
		if (entity.get() != obj && entity.get() != nullptr)
		{
			if (!entity->bIsStatic)
			{
				entity->CheckCollision(*obj);
			}
		}
	}
}