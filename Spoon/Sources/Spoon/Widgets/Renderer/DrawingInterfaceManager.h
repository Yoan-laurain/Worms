#pragma once

#include "DrawingInterface.h"
#include <memory>

class DrawingInterfaceManager 
{
    public:
        static DrawingInterfaceManager& getInstance();

        void setDrawingInterface(std::shared_ptr<DrawingInterface> interface);

        std::shared_ptr<DrawingInterface> getDrawingInterface() const;

    private:
        DrawingInterfaceManager() = default;
        std::shared_ptr<DrawingInterface> drawingInterface;
};