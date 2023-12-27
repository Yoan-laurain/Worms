#include "SGravityComponent.h"
#include "Spoon/Library/MathLibrary.h"
#include "Object/SActor.h"
#include <snpch.h>

SGravityComponent::SGravityComponent(SActor* owner) : SComponent(owner), bSimulateGravity(true)
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
		// acc : m/s�
		Velocity.Y += MathLibrary::Gravity*Deltatime;

#ifdef DEBUG
		std::cout << Velocity << std::endl;
#endif // DEBUG
		if (GetOwner())
			GetOwner()->SetLocation(GetOwner()->GetLocation() + (Velocity*Deltatime)*10); // Todo : faire en sorte que le size ne correspond plus au pixel.

	}
}
