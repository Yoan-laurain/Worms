#pragma once

#include "Core.h"
#include <snpch.h>

class SPOON_API InputHandler
{	
public:

	void BindInput(void* objRef, std::function<void()>& func);



};