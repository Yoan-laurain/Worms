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
        WidgetT* Widget = new WidgetT();
        if (Widget)
        {
            if (OwningObject)
            {
                Widget->SetParent(OwningObject);
            }

            WidgetManager::GetInstance()->AddWidget(std::shared_ptr<WidgetT>(Widget));

            return Widget;
        }

        assert(false, "Failed to create widget");

        return nullptr;
    }
};

