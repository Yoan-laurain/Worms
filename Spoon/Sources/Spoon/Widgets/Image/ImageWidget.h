#pragma once

#include "../Widget.h"
#include <string>

class SPOON_API ImageWidget : public Widget
{
    public:

        ImageWidget();

        void render(Window* window) override;
        void SetBackgroundImage(std::string imagePath);

    private:
        std::string imagePath;
};