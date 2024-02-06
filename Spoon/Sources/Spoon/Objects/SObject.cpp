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

void SObject::RemoveChild(SObject* child) 
{
    if (!child || Children.empty())
    {
        return;
    }

    auto it = std::find_if(Children.begin(), Children.end(), [&](const std::shared_ptr<SObject>& ptr) 
    {
       return ptr.get() == child;
    });

    if (it != Children.end()) 
    {
        Children.erase(it);
    }
}

void SObject::AddChild(std::shared_ptr<SObject> child)
{
	Children.push_back(child);
}