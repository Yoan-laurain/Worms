#pragma once
#include "Core.h"
#include "Window.h"
#include "Object/SActor.h"

#include <vector>

// TODO Levels
// je dois d�placer pour faire en sorte que ce soit pas � moi de faire �a.
// Faire en sorte d'avoir un objet levels qui gere tous seul les entit�s qui seront cr�e.
class SPOON_API Level
{
	std::mutex _mutex;

public:


	virtual ~Level();

	virtual void BeginPlay() = 0;

	void UpdateEntity(double deltatime);

	template<typename T = SActor>
	T* SpawnActor(const FTransform& transform)
	{
		T* tmp = new T();
		if (tmp)
		{
			tmp->SetTransform(transform);
			tmp->SetWorldRef(this);
		}
		// Cast vide du coup c mort.
		return tmp;
	}

	std::vector<SActor*> GetEntityList() const { return (bIsListBeingEdit) ? std::vector<SActor*>() : EntityList; }

	void RemoveObject(class SActor* obj);

	void AddObject(class SActor* obj);
	
protected:

	// Entity actuellement dans le world.
	std::vector<SActor*> EntityList;

	std::vector<SActor*> AddEntityList;

	bool bIsListBeingEdit = false;

};

