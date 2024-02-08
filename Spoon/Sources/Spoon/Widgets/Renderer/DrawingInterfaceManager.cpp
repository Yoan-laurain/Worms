#include "DrawingInterfaceManager.h"

DrawingInterfaceManager& DrawingInterfaceManager::getInstance() 
{
    static DrawingInterfaceManager instance;
    return instance;
}

void DrawingInterfaceManager::setDrawingInterface(std::shared_ptr<DrawingInterface> interface)
{
    drawingInterface = std::move(interface);
}

std::shared_ptr<DrawingInterface> DrawingInterfaceManager::getDrawingInterface() const
{
    return drawingInterface;
}
