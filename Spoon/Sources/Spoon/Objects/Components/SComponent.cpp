#include "SComponent.h"
#include <snpch.h>

SComponent::SComponent(SActor* owner) : 
	Owner(owner)
{}

void SComponent::SetName(const std::string& name)
{
	ComponentName = name;
}