
#include "SComponent.h"
#include <snpch.h>

SComponent::SComponent(SActor* owner) : 
	SObject(),
	Owner(owner)
{}

SComponent::~SComponent()
{}
