#pragma once

#include "DrawingWidgetInterface.h"
#include <memory>

class DrawingWidgetInterfaceManager 
{
    public:
        static DrawingWidgetInterfaceManager& getInstance();

        void setWidgetDrawingInterface(std::shared_ptr<DrawingWidgetInterface> interface);

        std::shared_ptr<DrawingWidgetInterface> getWidgetDrawingInterface() const;

    private:
        DrawingWidgetInterfaceManager() = default;
        std::shared_ptr<DrawingWidgetInterface> widgetDrawingInterface;
};