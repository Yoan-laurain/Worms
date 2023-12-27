#pragma once
#include "Spoon/Core/SObject.h"
#include "Spoon/Library/TColor.h"

class SComposant : public SObject
{
	friend class SActor;
public:

	SComposant() = default;

	SComposant(class SActor* owner = nullptr);

	virtual ~SComposant();

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
