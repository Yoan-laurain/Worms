#pragma once

#include "DrawingWidgetInterface.h"
#include "Core/Core.h"
#include <memory>

class SPOON_API DrawingWidgetInterfaceManager
{
    public:
        static DrawingWidgetInterfaceManager& GetInstance();

        void SetWidgetDrawingInterface(const std::shared_ptr<DrawingWidgetInterface>& Interface);

        std::shared_ptr<DrawingWidgetInterface> GetWidgetDrawingInterface() const;

    private:
        DrawingWidgetInterfaceManager() = default;
        std::shared_ptr<DrawingWidgetInterface> WidgetDrawingInterface;
};