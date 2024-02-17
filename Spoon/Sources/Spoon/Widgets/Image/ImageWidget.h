#pragma once

#include "../Widget.h"
#include <string>

class SPOON_API ImageWidget : public Widget
{
    public:

        ImageWidget() = default;
        virtual ~ImageWidget() override = default;

        void Render() override;
    
        std::string ImagePath{};
};