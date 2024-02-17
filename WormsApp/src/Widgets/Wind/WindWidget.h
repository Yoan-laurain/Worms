#pragma once

#include <Widgets/Widget.h>

class ImageWidget;

class WindWidget : public Widget
{
    public:
        WindWidget();
        ~WindWidget() override = default;
    
        void Init();
        void UpdateWindDirection(float WindDirection);

        void Render() override;

        ImageWidget* WindLogo;
        ImageWidget* WindDirection;
        
    protected:
        void Tick(float deltaTime) override;
};