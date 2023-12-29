#include "SGravityComponent.h"
#include "Library/MathLibrary.h"
#include "Objects/SActor.h"
#include <snpch.h>

SGravityComponent::SGravityComponent(SActor* owner) : SComponent(owner), bSimulateGravity(false)
{}

void SGravityComponent::Simulated(bool bSimulate)
{
	bSimulateGravity = bSimulate;
	if (!bSimulateGravity)
	{
		Velocity = 0;
	}
}

void SGravityComponent::OnUpdate(const float Deltatime)
{
	if (bSimulateGravity)
	{
		// velocity : m/s
		// acc : m/s²
		Velocity.Y += MathLibrary::Gravity*Deltatime;

		if (GetOwner())
			GetOwner()->SetLocation(GetOwner()->GetLocation() + (Velocity*Deltatime)); // Todo : faire en sorte que le size ne correspond plus au pixel.

	}
}
