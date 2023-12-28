#pragma once

#include "SComponent.h"
#include "Spoon/Library/TVector.h"

class SPOON_API SGravityComponent : public SComponent
{
public:
	
	SGravityComponent(class SActor* owner);

	void Simulated(bool bSimulate = true);

protected:

	virtual void OnUpdate(const float Deltatime) override;

	bool bSimulateGravity;

private:

	FVector2D Velocity;
	
};

