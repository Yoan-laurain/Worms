#include "SComponent.h"
#include <snpch.h>

SComponent::SComponent(SActor* owner) : 
	Owner(owner)
{}

SComponent::~SComponent()
{
#if DEBUG
	std::cout << "Component Destroy" << std::endl;
#endif // DEBUG
}

void SComponent::SetName(const std::string& name)
{
	ComponentName = name;
}