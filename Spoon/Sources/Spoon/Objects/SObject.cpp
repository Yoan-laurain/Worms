#include "SObject.h"
#include <snpch.h>

SObject::SObject() : UniqueId(0)
{
	UniqueId = reinterpret_cast<uint64>(this);
}

SObject::~SObject()
{
#if DEBUG
	std::cout << GetUniqueId() << " is destroyed" << std::endl;
#endif
}

