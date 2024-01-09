#pragma once

#include "Objects/SObject.h"
#include "Library/TColor.h"
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

	void DestroyActor();

	inline class Level* GetWorld() const { return WorldRef; };

	/************************************************************************/
	/* Transform															*/
	/************************************************************************/

	FVector2D GetLocation() const;

	void SetLocation(const FVector2D& loc);
	virtual void Move(const FVector2D& loc);

	FVector2D GetSize() const;

	void SetSize(const FVector2D& size);

	FTransform GetTransform() const;

	void SetTransform(const FTransform& transform);

	/************************************************************************/
	/* Collision															*/
	/************************************************************************/

	virtual bool IsInBound(const FVector2D& _loc);

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

protected:

	// Funciton called lorsque l'objet est ajouté à la list update
	virtual void BeginPlay();

	// Function called à chaque boucle du LogicThread
	virtual void Tick(float DeltaTime);

	bool OnMouseEvent(class MouseMovedEvent& _event);

	virtual bool OnMousePressedEvent(class MouseButtonPressedEvent& _event);

	virtual bool OnMouseRelesedEvent(class MouseButtonReleasedEvent& _event);

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

	void SetWorldRef(class Level* parentRef);

	void Step(float DeltaTime);

public:

	bool bIsStatic; // Can be moved
	bool bIsColliding;

	// physics
	FVector2D LinearVelocity;
	float RotationalVelocity;
	float Restitution;
	float Mass;
	float InvMass;
	float Magnitude;
	FVector2D Force;
	FVector2D Gravity;

	bool bNeedToUpdateBoundingBox;
	AlignAxisBoundingBox AABB;

	virtual void AddForce(const FVector2D& force);

protected:

	bool bIsHovered;

	bool bIsPressed;

	FVector2D mouseLoc;

	FTransform ObjectTransform;

private:

	std::vector<std::unique_ptr<class SComponent>> ComponentList;

	std::vector<class SComponent> TickableComponent;

	class Level* WorldRef;

};

class SPOON_API IPrefab
{
	virtual class SShapeComponent* GetShapeComponent() const = 0;
};
