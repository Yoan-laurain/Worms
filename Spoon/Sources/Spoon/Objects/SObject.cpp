#include "SObject.h"
#include <snpch.h>

SObject::SObject() : UniqueId(0)
{
	UniqueId = reinterpret_cast<unsigned long long>(this);
}

SObject::~SObject()
{
#if DEBUG
	std::cout << "Object Destroy : " << GetClassName() << std::endl;
#endif // DEBUG

}

