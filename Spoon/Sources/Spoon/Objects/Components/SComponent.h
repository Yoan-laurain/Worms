#pragma once

#include "Objects/SObject.h"

class SActor;

class SPOON_API SComponent : public SObject
{
	friend class SActor;

	GENERATE()

public:

	SComponent(class SActor* owner = nullptr);

	virtual ~SComponent() override;

	template <typename T = SActor>
	T* GetOwner() const
	{
		return (Owner) ? (T*)Owner : nullptr;
	}

	std::string GetName() const { return ComponentName; }

protected:

	virtual void OnUpdate(const float Deltatime) {}

private:

	void SetName(const std::string& name);

private:

	SActor* Owner;

	std::string ComponentName;
};