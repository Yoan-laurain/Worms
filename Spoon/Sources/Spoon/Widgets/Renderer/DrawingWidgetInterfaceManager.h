#pragma once

#include "DrawingWidgetInterface.h"
#include "Core/Core.h"
#include <memory>

class SPOON_API DrawingWidgetInterfaceManager
{
    public:
        static DrawingWidgetInterfaceManager& getInstance();

        void setWidgetDrawingInterface(std::shared_ptr<DrawingWidgetInterface> interface);

        std::shared_ptr<DrawingWidgetInterface> getWidgetDrawingInterface() const;

    private:
        DrawingWidgetInterfaceManager() = default;
        std::shared_ptr<DrawingWidgetInterface> widgetDrawingInterface;
};