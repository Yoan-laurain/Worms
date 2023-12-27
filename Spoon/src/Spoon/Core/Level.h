#pragma once
#include "Core.h"
#include "Window.h"
#include "Object/SActor.h"

// TODO Levels
// je dois déplacer pour faire en sorte que ce soit pas à moi de faire ça.
// Faire en sorte d'avoir un objet levels qui gere tous seul les entités qui seront crée.
class SPOON_API Level
{
	friend class Application;
	std::mutex _mutex;

public:

	virtual ~Level();

	// Le DestroyObject might not work so be carefull
	void DestroyObject(class SActor* _actor);

	template<typename T = class SActor>
	std::shared_ptr<T> SpawnActor(const FTransform& transform)
	{
		std::shared_ptr<T> tmp = std::make_shared<T>();
		if (tmp.get())
		{
			tmp->SetTransform(transform);
			tmp->SetWorldRef(this);
			AddObject(tmp);
		}
		// Cast vide du coup c mort.
		return tmp;
	}

	std::vector<std::shared_ptr<SActor>> GetEntityList() const { return (bIsListBeingEdit) ? std::vector<std::shared_ptr<SActor>>() : EntityList; }

protected:

	virtual void BeginPlay() = 0;

private:

	void UpdateEntity(double deltatime);

	void RemoveObject(std::shared_ptr<class SActor> obj);

	void AddObject(std::shared_ptr<class SActor> obj);
	
protected:

	// Entity actuellement dans le world.
	std::vector<std::shared_ptr<SActor>> EntityList;

	std::vector<std::shared_ptr<SActor>> AddEntityList;

	bool bIsListBeingEdit = false;

};

