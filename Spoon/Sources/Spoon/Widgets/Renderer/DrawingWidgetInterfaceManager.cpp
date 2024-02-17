#include "DrawingWidgetInterfaceManager.h"

DrawingWidgetInterfaceManager& DrawingWidgetInterfaceManager::GetInstance() 
{
    static DrawingWidgetInterfaceManager Instance;
    return Instance;
}

void DrawingWidgetInterfaceManager::SetWidgetDrawingInterface(const std::shared_ptr<DrawingWidgetInterface>& Interface)
{
    WidgetDrawingInterface = Interface;
}

std::shared_ptr<DrawingWidgetInterface> DrawingWidgetInterfaceManager::GetWidgetDrawingInterface() const
{
    return WidgetDrawingInterface;
}