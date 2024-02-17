#pragma once

#include "Objects/SObject.h"
#include "Library/TStruct.h"
#include "Components/SComponent.h"
#include <Library/AlignAxisBoudingBox.h>

class SPOON_API SActor : public SObject
{
	GENERATE()

private:

	friend class Level;

	// Todo : A delete when key application
	friend class Application;

	std::mutex _mutex;

public:

	SActor();

	virtual ~SActor();

	void MarkActorToDestruction();
	void DestroyActor();

	Level* GetWorld() const { return WorldRef; };

	/************************************************************************/
	/* Transform															*/
	/************************************************************************/

	FVector2D GetLocation() const;

	void SetLocation(const FVector2D& loc);
	virtual void Move(const FVector2D& loc);

	FVector2D GetSize() const;
	FVector2D GetForwardVector() const;

	void SetSize(const FVector2D& size);

	FTransform GetTransform() const;

	virtual void SetTransform(const FTransform& transform);

	/************************************************************************/
	/* Collision															*/
	/************************************************************************/

	virtual bool IsInBound(const FVector2D& _loc);
	virtual void OnCollide(SObject* Actor);

	/************************************************************************/
	/* Component Getter														*/
	/************************************************************************/

	// Get the component type of with a specific name
	template <typename T = SComponent>
	T* GetComponent(const std::string& name = "")
	{
		for (auto& comp : ComponentList)
		{
			if ( name.empty() || comp->GetName() == name)
				if (T* tmp = dynamic_cast<T*>(comp.get()))
					return tmp;

		}
		return nullptr;
	}

	// Get all Component of a specific type
	// Be careful, this function is not optimized
	template <typename T>
	bool GetAllComponentType(std::vector<T>& CompList) const
	{
		for (auto& comp : ComponentList)
		{
			if (T tmp = dynamic_cast<T>(comp.get()))
			{
				CompList.push_back(tmp);
			}
		}
		return !CompList.empty();
	}

	/************************************************************************/
	/* Physics															*/
	/************************************************************************/
	
	virtual void AddForce(const FVector2D& Force);
	float GetMass() const;
	void SetDensity(float Density);

protected:

	// Funciton called lorsque l'objet est ajouté à la list update
	virtual void BeginPlay();

	// Function called à chaque boucle du LogicThread
	virtual void Tick(float DeltaTime);
	
	// Function à called pour cree un component
	template<typename T>
	T* CreateComponent(const std::string& name)
	{
		T* tmp = new T(this);
		tmp->SetName(name);
		ComponentList.push_back(std::unique_ptr<T>(tmp));
		return tmp;
	}

private:

	// TODO faire add de component / Destroy Component

	void OnEvent(class SpoonEvent& event);

	void SetWorldRef(Level* parentRef);
	void ClampAcceleration();

	void UpdateObjectPhysics(float DeltaTime);

	void UpdateMass();

public:

	bool bIsStatic; // Can be moved
	bool bIsColliding;

	// physics
	FVector2D LinearVelocity;
	float RotationalVelocity;
	float Restitution;
	float Magnitude;
	float Density;
	bool bNeedToUpdateBoundingBox;
	AlignAxisBoundingBox AABB;

	float LifeSpan;
	bool bNeedToDestroy;

protected:
	
	FVector2D mouseLoc;

	FTransform ObjectTransform;

private:

	std::vector<std::unique_ptr<SComponent>> ComponentList;

	std::vector<SComponent> TickableComponent;

	Level* WorldRef;
	
	float Mass;
	float InvMass;

	FVector2D Force;
	FVector2D Gravity;
};