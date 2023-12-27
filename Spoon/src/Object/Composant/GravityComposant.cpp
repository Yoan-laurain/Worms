#include "GravityComposant.h"
#include "Spoon/Library/MathLibrary.h"
#include "Object/SActor.h"
#include <snpch.h>

GravityComposant::GravityComposant(SActor* owner) : SComposant(owner)
{
}

void GravityComposant::Simulated(bool bSimulate)
{
	bSimulateGravity = bSimulate;
	if (!bSimulateGravity)
	{
		Velocity = 0;
	}
}

void GravityComposant::OnUpdate(const float Deltatime)
{
	if (bSimulateGravity)
	{
		// velocity : m/s
		// acc : m/s²
		Velocity.Y += MathLibrary::Gravity*Deltatime;

#ifdef DEBUG
		std::cout << Velocity << std::endl;
#endif // DEBUG
		if (GetOwner())
			GetOwner()->SetLocation(GetOwner()->GetLocation() + (Velocity*Deltatime)*10); // Todo : faire en sorte que le size ne correspond plus au pixel.

	}
}
