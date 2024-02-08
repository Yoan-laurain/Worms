#include "SObject.h"
#include "Spoon/Widgets/Widget.h"

#include <snpch.h>
#include <Widgets/WidgetManager.h>

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