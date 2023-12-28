
#include "SComponent.h"
#include <snpch.h>

SComponent::SComponent(SActor* owner) : 
	SObject(),
	Owner(owner)
{}

SComponent::~SComponent()
{
#if DEBUG
	std::cout << "Component Destroy" << std::endl;
#endif // DEBUG
}
