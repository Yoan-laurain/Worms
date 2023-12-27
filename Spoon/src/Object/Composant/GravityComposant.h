#pragma once

#include "SComposant.h"

class SPOON_API GravityComposant : public SComposant
{
public:
	
	GravityComposant(class SActor* owner);

	void Simulated(bool bSimulate = true);

protected:

	virtual void OnUpdate(const float Deltatime) override;

protected:

	bool bSimulateGravity = true;

private:

	FVector2D Velocity;
	
};

