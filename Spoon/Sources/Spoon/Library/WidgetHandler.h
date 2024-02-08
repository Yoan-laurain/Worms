#pragma once

#include "Core/Core.h"
#include "Objects/SObject.h"
#include "snpch.h"
#include "Widgets/WidgetManager.h"
#include "Widgets/Widget.h"

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
            widget->SetParent(std::unique_ptr<SObject>(OwningObject)); 

            WidgetManager::GetInstance()->AddWidget(std::shared_ptr<WidgetT>(widget));

            return widget;
        }

        assert(false, "Failed to create widget");

        return nullptr;
    };
};

