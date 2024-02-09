#include "DrawingWidgetInterfaceManager.h"

DrawingWidgetInterfaceManager& DrawingWidgetInterfaceManager::getInstance() 
{
    static DrawingWidgetInterfaceManager instance;
    return instance;
}

void DrawingWidgetInterfaceManager::setWidgetDrawingInterface(std::shared_ptr<DrawingWidgetInterface> interface)
{
    widgetDrawingInterface = std::move(interface);
}

std::shared_ptr<DrawingWidgetInterface> DrawingWidgetInterfaceManager::getWidgetDrawingInterface() const
{
    return widgetDrawingInterface;
}
