#pragma once

#include "../Widget.h"
#include <string>

class SPOON_API ImageWidget : public Widget
{
    public:

        ImageWidget();

        void render() override;
    
        std::string imagePath;
};