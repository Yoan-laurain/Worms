#include "DrawingInterfaceManager.h"

DrawingInterfaceManager& DrawingInterfaceManager::getInstance()
{
	static DrawingInterfaceManager instance;
	return instance;
}

std::shared_ptr<DrawingInterface> DrawingInterfaceManager::getDrawingInterface() const
{
	return drawingInterface; 
}

void DrawingInterfaceManager::setDrawingInterface(std::shared_ptr<DrawingInterface> drawingInterface)
{
	this->drawingInterface = drawingInterface;
}