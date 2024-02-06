#pragma once

#include "../Widget.h"
#include <string>

class ImageWidget : public Widget 
{
    public:

        ImageWidget();

        void render();
        void SetBackgroundImage(std::string imagePath);

    private:
        std::string imagePath;
};