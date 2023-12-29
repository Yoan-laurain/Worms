#pragma once
#include "Objects/SObject.h"
#include "Library/TColor.h"

class SPOON_API SComponent : public SObject
{
	friend class SActor;

	GENERATE()

public:

	SComponent(class SActor* owner = nullptr);

	virtual ~SComponent();

	template <typename T = class SActor>
	T* GetOwner() const
	{
		return (Owner) ? (T*)Owner : nullptr;
	}

	std::string GetName() const { return ComponentName; }

protected:

	virtual void OnUpdate(const float Deltatime) {};

private:

	void SetName(const std::string& name);

private:

	class SActor* Owner;

	std::string ComponentName;

};
