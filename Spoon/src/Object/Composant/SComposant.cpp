
#include "SComposant.h"
#include <snpch.h>

SComposant::SComposant(SComposant* owner) : 
	SObject(),
	Owner(owner)
{}

SComposant::~SComposant()
{}


bool const SComposant::IsInBound(const FVector2D& loc) const
{
	const FVector2D halfSize = GetSize();
	const FVector2D minSize = GetLocation() - halfSize;
	const FVector2D maxSize = GetLocation() + halfSize;

	const bool bIsInbound = loc <= maxSize && loc >= minSize;

#ifdef DEBUG
	std::cout << "Mouse : " << loc << " -> min : " << minSize << " max : " << maxSize << std::endl;
	std::cout << "IsInbound : " << bIsInbound << std::endl;
#endif

	return bIsInbound;
}
