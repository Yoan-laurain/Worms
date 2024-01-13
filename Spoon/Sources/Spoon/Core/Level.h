#pragma once
#include "Core.h"
#include "Window.h"
#include "Objects/SActor.h"
#include "Library/Manifold.h"

class SActor;

// TODO Levels
// je dois déplacer pour faire en sorte que ce soit pas à moi de faire ça.
// Faire en sorte d'avoir un objet levels qui gere tous seul les entités qui seront crée.
class SPOON_API Level
{
	friend class Application;
	std::mutex _mutex;

public:

	Level();
	virtual ~Level();

	// Le DestroyObject might not work so be carefull
	void DestroyObject(SActor* _actor);

	template<typename T>
	T* SpawnActor(const FTransform& transform)
	{
		T* tmp = new T();
		if (tmp)
		{
			tmp->SetTransform(transform);
			tmp->SetWorldRef(this);
			AddObject(tmp);
		}
		// Cast vide du coup c mort.
		return tmp;
	}

protected:
	
	void HandleCollision(SActor* obj);
	virtual void BeginPlay() = 0;

private:

	void UpdateEntity(double deltatime);
	void ResolveCollision(Manifold& contact);

	AlignAxisBoundingBox& GetAABB(SActor* obj);
	void HandleObjectOutOfWindow(SActor* obj);	

	// TODO Change to be able to change the ownership
	void RemoveObject(SActor* obj);

	void AddObject(SActor* obj);

	void NarrowPhase(SActor* entity, SActor* obj);

protected:

	// Entity actuellement dans le world.
	std::vector<std::unique_ptr<SActor>> EntityList;

	std::vector<std::unique_ptr<SActor>> AddEntityList;

	bool bIsListBeingEdit = false;

};