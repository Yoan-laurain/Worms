#pragma once

#include "Core/Core.h"
#include "snpch.h"
#include "Objects/SObject.h"
#include "Widgets/WidgetManager.h"

struct SPOON_API WidgetHandler
{
    template <typename WidgetT>
    static WidgetT* CreateWidget(SObject* OwningObject)
    {
        if (!OwningObject)
        {
            assert(false, " The owning object of the widget is null");
            return nullptr;
        }

        WidgetT* widget = new WidgetT();
        if (widget)
        {
            widget->SetParent(OwningObject); 

            WidgetManager::GetInstance()->AddWidget(std::shared_ptr<WidgetT>(widget));

            return widget;
        }

        assert(false, "Failed to create widget");

        return nullptr;
    }
};

