#pragma once
#include "Spoon/Core/SObject.h"
#include "Spoon/Library/TColor.h"

class SPOON_API SComponent : public SObject
{
	friend class SActor;
public:

	SComponent(class SActor* owner = nullptr);

	virtual ~SComponent();

	template <typename T = class SActor>
	T* GetOwner() const
	{
		return (T*)Owner;
	}

protected:

	virtual void OnUpdate(const float Deltatime) {};

private:

	class SActor* Owner;

};
